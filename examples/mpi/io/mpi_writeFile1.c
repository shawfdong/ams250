/* write to a common file using explicit offsets */
#include "mpi.h"
#define FILESIZE (1024 * 1024)
int main(int argc, char **argv) {
  int *buf, i, rank, size, bufsize, nints, offset;
  MPI_File fh;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); MPI_Comm_size(MPI_COMM_WORLD, &size);
  bufsize = FILESIZE/size;
  buf = (int *) malloc(bufsize);
  nints = bufsize/sizeof(int);
  for (i=0; i<nints; i++) buf[i] = rank*nints + i;
  offset = rank*bufsize;
  MPI_File_open(MPI_COMM_WORLD, "datafile", MPI_MODE_CREATE|MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh);
  MPI_File_write_at(fh, offset, buf, nints, MPI_INT, &status);
  MPI_File_close(&fh); free(buf);
  MPI_Finalize();
  return 0;
}
