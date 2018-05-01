#include "ga.h"
int ga_read_inc(GA ga, int i, int j, int inc)
{
  MPI_Aint disp;
  int      rank, one = 1, result;

  rank = (j - 1) / ga->chunk2;

  /* disp depends on the displacement unit being sizeof(int) */
  disp = (j - 1 - (rank * ga->chunk2)) * ga->dim1 + i - 1;

  MPI_Win_lock(MPI_LOCK_SHARED, rank, MPI_MODE_NOCHECK, ga->ga_win);
  MPI_Fetch_and_op(&one, &result, MPI_INT, rank, disp, MPI_SUM,
                   ga->ga_win);
  MPI_Win_unlock(rank, ga->ga_win);

  return result;
}
