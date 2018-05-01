#include "mpi.h"

int MPE_Blocking_put(const void *buf, int count,
                     MPI_Datatype dtype, int target_rank,
                     MPI_Aint target_offset, int target_count,
                     MPI_Datatype target_dtype, MPI_Win win)
{
    int err;

    MPI_Win_lock(MPI_LOCK_SHARED, target_rank, 0, win);
    err = MPI_Put(buf, count, dtype, target_rank, target_offset,
                  target_count, target_dtype, win);
    MPI_Win_unlock(target_rank, win);
    return err;
}
