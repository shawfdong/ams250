#include "mpi.h"
#include <string.h>

#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 1024
int MPIX_T_cvar_get_index(const char *name, int *cidxPtr)
{
    int          num_cvar, cidx, nameLen, descLen, verbosity, binding, scope,
	err;
    char         desc[MAX_DESC_LEN];
    char         cname[MAX_NAME_LEN];
    MPI_T_enum   enumtype;
    MPI_Datatype datatype;

    /* Find the index for the desired variable */
    MPI_T_cvar_get_num( &num_cvar );
    for (cidx=0; cidx<num_cvar; cidx++) {
	nameLen = sizeof(name); descLen = sizeof(desc);
	err = MPI_T_cvar_get_info(cidx, cname, &nameLen, &verbosity,
                  &datatype, &enumtype, desc, &descLen, &binding, &scope);
	if (strcmp(name, cname) == 0) break;
    }
    /* If we fail to find the name, return an error.  There is no MPI_T
       error for this case in MPI 3.0, but INVALID_INDEX is close. */
    if (cidx == num_cvar) return MPI_T_ERR_INVALID_INDEX;
    *cidxPtr = cidx;
    return MPI_SUCCESS;
}
