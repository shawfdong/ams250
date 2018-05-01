#include <stdio.h>
#include "mpi.h"
#include "ic_nxtval.h"

#define SERVER_RANK 0
int MPE_Counter_nxtval_ic(MPI_Comm counter_comm, int *value)
{
   /* always request/receive services from
      intercomm (remote) rank=0 */
   MPI_Send(NULL, 0, MPI_INT, SERVER_RANK, REQUEST, counter_comm);
   MPI_Recv(value, 1, MPI_INT, SERVER_RANK, VALUE, counter_comm,
            MPI_STATUS_IGNORE);
   return 0;
}
