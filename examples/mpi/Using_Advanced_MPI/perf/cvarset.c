#include <stdio.h>
#include "mpi.h"
#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 1024
int main(int argc, char *argv[] )
{
  int          cidx, eagersize, nvals, err;
  int          required = MPI_THREAD_SINGLE, provided;
  MPI_T_cvar_handle chandle;
  MPI_T_enum   enumtype;
  MPI_Datatype datatype;

  MPI_Init_thread(0, 0, required, &provided);
  MPI_T_init_thread(required, &provided);

  /* Lookup the index for the desired variable */
  err = MPI_T_cvar_get_index("MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE",  
                             &cidx);
  if (err != MPI_SUCCESS) MPI_Abort(0, MPI_COMM_WORLD);

  /* Create a handle for it */
  err = MPI_T_cvar_handle_alloc(cidx, NULL, &chandle, 
                                &nvals);
  if (nvals != 1) 
    printf("Unexpected number of values = %d\n", nvals);

  err = MPI_T_cvar_read(chandle, &eagersize);
  printf("Eager size = %d\n", eagersize);

  eagersize = 1024;
  err = MPI_T_cvar_write(chandle, &eagersize);
  err = MPI_T_cvar_read(chandle, &eagersize);
  if (eagersize != 1024) printf("Failed to reset eagersize!\n");

  MPI_T_cvar_handle_free(&chandle);
  MPI_T_finalize();  /* No test on return because we're about 
                        to exit */
  MPI_Finalize();
}
