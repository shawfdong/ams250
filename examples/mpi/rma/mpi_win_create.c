#include "mpi.h"
int main(int argc, char ** argv)
{
    int *a;
    MPI_Win win;
    MPI_Init(&argc, &argv);
    /* create private memory */
    a = (void *) malloc(1000 * sizeof(int));
    /* use private memory like you normally would */
    a[0] = 1;  a[1] = 2;
    /* collectively declare memory as remotely accessible */
    MPI_Win_create(a, 1000*sizeof(int), sizeof(int),
                   MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    /* Array 'a' is now accessibly by all processes in MPI_COMM_WORLD */
    MPI_Win_free(&win);
    free(a);
    MPI_Finalize();
    return 0;
}
