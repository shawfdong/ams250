#include "mpi.h"
int main(int argc, char ** argv)
{
    int *a;
    MPI_Win win;
    MPI_Init(&argc, &argv);

    /* collectively create remotely accessible memory in the window */
    MPI_Win_allocate(1000, sizeof(int), MPI_INFO_NULL,
                     MPI_COMM_WORLD, &a, &win);

    /* Array 'a' is now accessibly by all processes in MPI_COMM_WORLD */
    MPI_Win_free(&win);

    MPI_Finalize();
    return 0;
}
