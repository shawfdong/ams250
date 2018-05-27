/* write to a common file using shared file pointer */
#include "mpi.h"
int main(int argc, char **argv) {
  int buf[1000];
  MPI_File fh;
  MPI_Init(&argc, &argv);
  MPI_File_open(MPI_COMM_WORLD, "datafile", MPI_MODE_CREATE|MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh);
  MPI_File_write_shared(fh, buf, 1000, MPI_INT, MPI_STATUS_IGNORE);
  MPI_File_close(&fh);
  MPI_Finalize();
  return 0;
}
