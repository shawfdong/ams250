#include "mpi.h"
void exchng1(int nx, int s, int e, double a[nx+2][e-s+1],
	     MPI_Comm comm1d, int nbrbottom, int nbrtop)
{
  MPI_Request req[4];
  int         ny = e - s + 1;

  MPI_Irecv(&a[1][0],    nx, MPI_DOUBLE, nbrbottom,
            0, comm1d, &req[0]);
  MPI_Irecv(&a[1][ny-1], nx, MPI_DOUBLE, nbrtop,
            1, comm1d, &req[1]);
  MPI_Isend(&a[1][ny-2], nx, MPI_DOUBLE, nbrtop,
            0, comm1d, &req[2]);
  MPI_Isend(&a[1][1],    nx, MPI_DOUBLE, nbrbottom,
            1, comm1d, &req[3]);
  MPI_Waitall(4, req, MPI_STATUSES_IGNORE);
}
