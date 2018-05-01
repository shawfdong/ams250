#include "mpi.h"

int MPI_T_pvar_get_index(const char *pname, int pclass, int *pidxPtr)
{
    int     err, i, numPvar, nameLen, descLen, binding;
    int     verbosity, varClass, isReadonly, isContinuous, isAtomic;
    char         name[128];
    MPI_T_enum   enumtype;
    MPI_Datatype datatype;

    err = MPI_T_pvar_get_num( &numPvar );
    if (err) return err;

    for (i=0; i<numPvar; i++) {
        nameLen = sizeof(name);
        descLen = 0;
        err = MPI_T_pvar_get_info( i, name, &nameLen, &verbosity, &varClass,
                             &datatype, &enumtype, NULL, &descLen, &binding,
                             &isReadonly, &isContinuous, &isAtomic );
        if (err) return err;
	if (strcmp(name, pname) == 0 && pclass == varClass) break;
    }
    if (i == numPvar) {
    }
    *pidxPtr = i;
    return MPI_SUCCESS;
}
