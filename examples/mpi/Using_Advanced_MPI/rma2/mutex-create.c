#include "mpi.h"
int MPE_MUTEX_KEYVAL = MPI_KEYVAL_INVALID;

int MPE_Mutex_create(MPI_Comm comm, int num, MPI_Win *mutex_win)
{
  int rank, size, *counterMem=0;
  int lnum, lleft, i;
  MPI_Aint counterSize = 0;

  MPI_Comm_rank(comm,&rank);
  MPI_Comm_size(comm,&size);
  lnum  = num / size;
  lleft = num % size;
  if (rank < lleft) lnum++;
  counterSize = lnum * sizeof(int);
  if (counterSize > 0) {
    MPI_Alloc_mem(counterSize, MPI_INFO_NULL, &counterMem);
    for (i=0; i<lnum; i++) counterMem[i] = 0;
  }
  MPI_Win_create(counterMem, counterSize, sizeof(int),
		 MPI_INFO_NULL, MPI_COMM_WORLD, mutex_win);
  if (MPE_MUTEX_KEYVAL == MPI_KEYVAL_INVALID) {
    MPI_Win_create_keyval(MPI_WIN_NULL_COPY_FN, MPI_WIN_NULL_DELETE_FN,
			  &MPE_MUTEX_KEYVAL, (void*)0);
  }
  MPI_Win_set_attr(*mutex_win, MPE_MUTEX_KEYVAL, (void*)(MPI_Aint)(size));
  return 0;
}

int MPE_Mutex_free(MPI_Win *mutex_win)
{
  int flag, *counterMem;

  MPI_Win_get_attr(*mutex_win, MPI_WIN_BASE, &counterMem, &flag);
  if (flag && counterMem != 0) {
    MPI_Free_mem(counterMem);
  }
  MPI_Win_free(mutex_win);
  return 0;
}
