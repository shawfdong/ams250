#include "mpi.h"
int main(int argc, char ** argv)
{
    int *a;
    MPI_Win win;
    MPI_Init(&argc, &argv);
    MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    /* create private memory */
    a = (void *) malloc(1000 * sizeof(int));
    /* use private memory like you normally would */
    a[0] = 1;  a[1] = 2;
    /* locally declare memory as remotely accessible */
    MPI_Win_attach(win, a, 1000);
    /* Array 'a' is now accessible from all processes in MPI_COMM_WORLD */
    /* undeclare public memory */
    MPI_Win_detach(win, a);
    MPI_Win_free(&win);
    MPI_Finalize(); return 0;
}
