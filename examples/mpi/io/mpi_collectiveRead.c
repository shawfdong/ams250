/* noncontiguous access with a single collective I/O function */
#include "mpi.h"
#define FILESIZE 1048576
#define INTS_PER_BLK 16
int main (int argc, char **argv)
{
  int *buf, rank, size, nints, bufsize;
  MPI_File fh ;
  MPI_Datatype filetype;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  bufsize = FILESIZE/size;
  buf = (int *) malloc(bufsize);
  nints = bufsize/sizeof(int);
  MPI_File_open(MPI_COMM_WORLD, "datafile", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
  MPI_Type_vector(nints/INTS_PER_BLK, INTS_PER_BLK,
                  INTS_PER_BLK*size, MPI_INT, &filetype);
  MPI_Type_commit(&filetype);
  MPI_File_set_view(fh, INTS_PER_BLK*sizeof(int)*rank, MPI_INT,
                    filetype, "native", MPI_INFO_NULL);
  MPI_File_read_all(fh, buf, nints, MPI_INT, MPI_STATUS_IGNORE);
  MPI_File_close(&fh);
  MPI_Type_free(&filetype);
  free(buf);
  MPI_Finalize();
  return 0 ;
}
