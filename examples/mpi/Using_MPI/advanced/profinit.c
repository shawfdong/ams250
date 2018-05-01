#include <stdio.h>
#include "mpi.h"
#include "mpe.h"

int MPI_Init(int *argc, char ***argv)
{
    int procid, returnVal;
    returnVal = PMPI_Init(argc, argv);
    MPE_Initlog();
    PMPI_Comm_rank(MPI_COMM_WORLD, &procid);
    if (procid == 0) {
	MPE_Describe_state(S_SEND_EVENT, E_SEND_EVENT,
			   "Send", "blue:gray3");
	MPE_Describe_state(S_RECV_EVENT, E_RECV_EVENT,
			   "Recv", "green:light_gray");
        ...
    }
    return returnVal;
}
