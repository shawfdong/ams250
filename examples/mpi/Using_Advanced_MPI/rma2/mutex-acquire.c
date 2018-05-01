#include "mpi.h"
extern int MPE_MUTEX_KEYVAL;
int MPE_Mutex_acquire(MPI_Win mutex_win, int num) {
  int      mone = -1, one=1, oldval;
  int      lrank, flag, size, *attrval;
  MPI_Aint lidx;

  /* Compute the location of the counter */
  MPI_Win_get_attr(mutex_win, MPE_MUTEX_KEYVAL, &attrval, &flag);
  if (!flag) return -1;  /* Error: counterWin not setup */
  size = (int)(MPI_Aint)attrval;  /* We stored the integer as a
                                     pointer */
  lrank = num % size; lidx  = num / size;

  MPI_Win_lock(MPI_LOCK_SHARED, lrank, 0, mutex_win);
  do {
    MPI_Fetch_and_op(&one, &oldval, MPI_INT,
                     lrank, lidx, MPI_SUM, mutex_win);
    MPI_Win_flush(lrank, mutex_win);
    if (oldval == 0) break;
    MPI_Accumulate(&mone, 1, MPI_INT, lrank, lidx, 1, MPI_INT,
                   MPI_SUM, mutex_win);
    MPI_Win_flush(lrank, mutex_win);
    /* We could wait a little bit, depending on oldval */
  } while (1);
  MPI_Win_unlock(lrank, mutex_win);
  return 0;
}
