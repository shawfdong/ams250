#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int          provided, err;
  int          numPvar, nameLen, descLen, verbosity, varClass;
  int          binding, isReadonly, isContinuous, isAtomic, i;
  char         name[128], desc[1024];
  MPI_T_enum   enumtype;
  MPI_Datatype datatype;

  MPI_Init_thread(0, 0, MPI_THREAD_SINGLE, &provided);
  err = MPI_T_init_thread(MPI_THREAD_SINGLE, &provided);
  if (err) MPI_Abort(MPI_COMM_WORLD, 0);

  err = MPI_T_pvar_get_num(&numPvar);
  if (err) MPI_Abort(MPI_COMM_WORLD, 0);
  printf("%d MPI Performance Variables\n", numPvar);

  for (i=0; i<numPvar; i++) {
   nameLen = sizeof(name);
   descLen = sizeof(desc);
   err = MPI_T_pvar_get_info(i, name, &nameLen, &verbosity,
                        &varClass, &datatype, &enumtype, desc,
                        &descLen, &binding, &isReadonly,
                        &isContinuous, &isAtomic);
   if (err) MPI_Abort(MPI_COMM_WORLD, 0);
   printf("\t%s\tClass=%d\tReadonly=%s\tContinuous=%s\tAtomic=%s\t%s\n",
    name, varClass, isReadonly ? "T" : "F",
    isContinuous ? "T" : "F", isAtomic ? "T" : "F", desc);
  }
 MPI_T_finalize();  /* No test on return because we're about
                       to exit */
 MPI_Finalize();
 return 0;
}
