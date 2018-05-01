#include "mpi.h"
#include "nxtval.h"
#include <stdio.h>

int main( int argc, char *argv[] )
{
  MPI_Comm counter_comm, worker_comm;

  MPI_Init( &argc, &argv );

  MPE_Counter_create( MPI_COMM_WORLD, &worker_comm, &counter_comm );

  if (worker_comm != MPI_COMM_NULL) {
    /* I am one of the workers; the master doesn't exit create until
       MPE_Counter_free is called */
    int value, rank;
    MPI_Comm_rank( counter_comm, &rank );
    MPE_Counter_nxtval( counter_comm, &value );
    printf( "[%d] received value %d\n", rank, value );
    MPE_Counter_free( &worker_comm, &counter_comm );
  }

  MPI_Finalize( );
  return 0;
}
