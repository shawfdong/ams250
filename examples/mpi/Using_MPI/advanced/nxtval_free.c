#include <stdio.h>
#include "mpi.h"
#include "nxtval.h"

int MPE_Counter_free(MPI_Comm *smaller_comm,
                     MPI_Comm *counter_comm)
{
    int myid, numprocs;
    MPI_Comm_rank(*counter_comm, &myid);
    MPI_Comm_size(*counter_comm, &numprocs);
    /* Make sure that all requests have been serviced */
    if (myid == 0)
        MPI_Send(NULL, 0, MPI_INT, numprocs-1, GOAWAY,
                 *counter_comm);
    MPI_Comm_free(counter_comm);
    if (*smaller_comm != MPI_COMM_NULL) {
        MPI_Comm_free(smaller_comm);
    }
    return 0;
}
