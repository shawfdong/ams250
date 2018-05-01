#include "mpi.h"

static int MCS_LOCKRANK = MPI_KEYVAL_INVALID;
enum { nextRank=0, blocked=1, lockTail=2 };

void MCSLockInit(MPI_Comm comm, MPI_Win *win)
{
  int      *lmem, rank;
  MPI_Aint winsize;
  MPI_Comm_rank(comm,&rank);

  if (MCS_LOCKRANK == MPI_KEYVAL_INVALID)
    MPI_Win_create_keyval(MPI_WIN_NULL_COPY_FN,
			  MPI_WIN_NULL_DELETE_FN,
			  &MCS_LOCKRANK, (void*)0);

  winsize = 2 * sizeof(int);
  if (rank == 0) winsize += sizeof(int);
  MPI_Win_allocate(winsize, sizeof(int), MPI_INFO_NULL, comm,
                   &lmem, win);
  lmem[nextRank] = -1;
  lmem[blocked]  = 0;
  if (rank == 0) {
    lmem[lockTail] = -1;
  }
  MPI_Win_set_attr(*win, MCS_LOCKRANK, (void*)(MPI_Aint)rank);
  MPI_Barrier(comm);
}

void MCSLockAcquire(MPI_Win win)
{
  int  flag, myrank, predecessor, *lmem;
  void *attrval;

  MPI_Win_get_attr(win, MCS_LOCKRANK, &attrval, &flag);
  myrank = (int)(MPI_Aint)attrval;
  MPI_Win_get_attr(win, MPI_WIN_BASE, &lmem, &flag);
  lmem[blocked] = 1; /* In case we are blocked */
  MPI_Win_lock_all(0, win);
  MPI_Fetch_and_op(&myrank, &predecessor, MPI_INT,
                   0, lockTail, MPI_REPLACE, win);
  MPI_Win_flush(0, win);
  if (predecessor != -1) {
    /* We didn't get the lock.  Add us to the tail of the list */
    MPI_Accumulate(&myrank, 1, MPI_INT, predecessor,
                   nextRank, 1, MPI_INT, MPI_REPLACE, win);
    /* Now spin on our local value "blocked" until we are
       given the lock */
    do {
      MPI_Win_sync(win);  /* Ensure memory updated */
    } while (lmem[blocked] == 1);
  }
  // else we have the lock
  MPI_Win_unlock_all(win);
}
void MCSLockRelease(MPI_Win win)
{
  int nullrank = -1, zero=0, myrank, curtail, flag, *lmem;
  void *attrval;

  MPI_Win_get_attr(win, MCS_LOCKRANK, &attrval, &flag);
  myrank = (int)(MPI_Aint)attrval;
  MPI_Win_get_attr(win, MPI_WIN_BASE, &lmem, &flag);
  MPI_Win_lock_all(0, win);
  if (lmem[nextRank] == -1) {
    /* See if we're waiting for the next to notify us */
    MPI_Compare_and_swap(&nullrank, &myrank, &curtail, MPI_INT,
                         0, lockTail, win);
    if (curtail == myrank) {
      /* We are the only process in the list */
      MPI_Win_unlock_all(win);
      return;
    }
    /* Otherwise, someone else has added themselves to the list.*/
    do {
      MPI_Win_sync(win);
    } while (lmem[nextRank] == -1);
  }
  /* Now we can notify them.  Use accumulate with replace instead 
     of put since we want an atomic update of the location */
  MPI_Accumulate(&zero, 1, MPI_INT, lmem[nextRank], blocked,
		 1, MPI_INT, MPI_REPLACE, win);
  MPI_Win_unlock_all(win);
}
