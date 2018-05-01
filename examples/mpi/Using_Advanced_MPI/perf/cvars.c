#include <stdio.h>
#include "mpi.h"

/* Lengths for statically allocated character arrays */
#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 1024
int main(int argc, char *argv[])
{
 int          i, num_cvar, nameLen, verbosity, descLen, binding;
 int          required = MPI_THREAD_SINGLE, provided, err, scope;
 char         name[MAX_NAME_LEN], desc[MAX_DESC_LEN];
 MPI_T_enum   enumtype;
 MPI_Datatype datatype;

 MPI_Init_thread(0, 0, required, &provided);
 MPI_T_init_thread(required, &provided);

 MPI_T_cvar_get_num(&num_cvar);
 printf("%d MPI Control Variables\n", num_cvar);
 for (i=0; i<num_cvar; i++) {
  nameLen = sizeof(name);
  descLen = sizeof(desc);
  err = MPI_T_cvar_get_info(i, name, &nameLen, &verbosity,
                                  &datatype, &enumtype, desc, 
                                  &descLen, &binding, &scope);

  printf("\t%-32s\t%s\n", name, desc);
 }

 MPI_T_finalize(); /* No test on return because we're 
                      about to exit */
 MPI_Finalize();
 return 0;
}
