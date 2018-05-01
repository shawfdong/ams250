#include <stdio.h>
#include "mpi.h"
#include "seqdef.h"

int main( int argc, char *argv[] )
{
  int wrank;
  MPI_Init( &argc, &argv );

  MPI_Comm_rank( MPI_COMM_WORLD, &wrank );
  seqBegin( MPI_COMM_WORLD );
  printf( "My rank is %d\n", wrank );
  fflush( stdout );
  seqEnd( MPI_COMM_WORLD );

  printf( "non-seq my rank = %d\n", wrank );
  MPI_Finalize();
  return 0;
}
