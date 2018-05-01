#include "mpi.h"
#include "mpe.h"
int MPI_Bcast(void *buf, int count, MPI_Datatype datatype,
	      int root, MPI_Comm comm)
{
    int result;

    MPE_Log_event(S_BCAST_EVENT, Bcast_ncalls, (char *)0);
    result = PMPI_Bcast(buf, count, datatype, root, comm);
    MPE_Log_event(E_BCAST_EVENT, Bcast_ncalls, (char *)0);
    return result;
}
