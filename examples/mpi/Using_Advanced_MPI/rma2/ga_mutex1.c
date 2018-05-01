#include "ga.h"
/* Instead of using a static variable, we could attach this to
   a communicator, using a communicator attribute */
static MPI_Win gamutex_win = MPI_WIN_NULL;
int ga_create_mutexes(int num)
{
  int rank, i, *counterMem = 0, countersize=0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    countersize = num * sizeof(int);
    MPI_Alloc_mem(countersize, MPI_INFO_NULL, &counterMem);
    for (i=0; i<num; i++)
      counterMem[i] = 0;
  }
  MPI_Win_create(counterMem, countersize, sizeof(int),
		 MPI_INFO_NULL, MPI_COMM_WORLD, &gamutex_win);
  return 0;
}
int ga_lock(int n)
{
  int mone = -1, one=1, oldval;

  MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, gamutex_win);
  do {
    MPI_Fetch_and_op(&one, &oldval, MPI_INT, 0, n, MPI_SUM,
		     gamutex_win);
    MPI_Win_flush(0, gamutex_win);
    if (oldval == 0) break;
    MPI_Accumulate(&mone, 1, MPI_INT, 0, n, 1, MPI_INT, MPI_SUM,
		   gamutex_win);
    MPI_Win_flush(0, gamutex_win);
    /* We could wait a little bit, depending on oldval */
  } while (1);
  MPI_Win_unlock(0, gamutex_win);
  return 0;
}
int ga_unlock(int n)
{
  int mone = -1;
  MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, gamutex_win);
  MPI_Accumulate(&mone, 1, MPI_INT, 0, n, 1, MPI_INT, MPI_SUM, gamutex_win);
  MPI_Win_unlock(0, gamutex_win);
  return 0;
}
