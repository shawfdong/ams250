#include <stdio.h>
#include "mpi.h"
#include "ic_nxtval.h"

#define SERVER_RANK 0
int MPE_Counter_free_ic(MPI_Comm *smaller_comm,
			MPI_Comm *counter_comm)
{
    int myid;
    MPI_Comm_rank(*smaller_comm, &myid);
    MPI_Barrier(*smaller_comm);
    if (myid == 0)
        MPI_Send(NULL, 0, MPI_INT, SERVER_RANK, GOAWAY,
                 *counter_comm);

    MPI_Comm_free(counter_comm);
    MPI_Comm_free(smaller_comm);

    return(0);
}
