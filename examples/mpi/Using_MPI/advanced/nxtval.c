#include <stdio.h>
#include "mpi.h"
#include "nxtval.h"

int MPE_Counter_nxtval(MPI_Comm counter_comm, int *value)
{
    int server,numprocs;
    MPI_Comm_size(counter_comm, &numprocs);
    server = numprocs-1;
    MPI_Send(NULL, 0, MPI_INT, server, REQUEST, counter_comm);
    MPI_Recv(value, 1, MPI_INT, server, VALUE, counter_comm,
             MPI_STATUS_IGNORE);
    return 0;
}
