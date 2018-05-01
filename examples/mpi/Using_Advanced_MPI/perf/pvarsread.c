#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int          provided, lcount, err, pidx, isContinuous;
  double       qtimestart, qtime;
  MPI_T_enum   enumtype;        MPI_Datatype datatype;
  MPI_T_pvar_session session;   MPI_T_pvar_handle  handle;

  MPI_Init_thread(0, 0, MPI_THREAD_SINGLE, &provided);
  err = MPI_T_init_thread(MPI_THREAD_SINGLE, &provided);
  if (err) MPI_Abort(MPI_COMM_WORLD, 0);

  err = MPI_T_pvar_get_index("time_matching_unexpectedq",
                             MPI_T_PVAR_CLASS_TIMER, &pidx);

  if (err != MPI_SUCCESS) MPI_Abort(MPI_COMM_WORLD, 0);
  /* Determine whether we need to start the variable. MPI 3.1
     allows us to pass NULL for any return parameter that 
     we ignore. */
  err = MPI_T_pvar_get_info(pidx, NULL, NULL, NULL, NULL,
		            NULL, NULL, NULL, NULL, NULL,
		            NULL, &isContinuous, NULL);

  err = MPI_T_pvar_session_create(&session);
  err = MPI_T_pvar_handle_alloc(session, pidx, NULL, &handle, 
                                &lcount);
  err = MPI_T_pvar_read(session, handle, &qtimestart);
  if (!isContinuous) err = MPI_T_pvar_start(session, handle);
  TestProgram();
  if (!isContinuous) err = MPI_T_pvar_stop(session, handle);
  err = MPI_T_pvar_read(session, handle, &qtime);
  printf("Time searching unexpected queue = %e\n", 
         qtime-qtimestart);
  /* No test on return from here on because we're about to 
     exit */
  MPI_T_pvar_handle_free(session, &handle);
  MPI_T_pvar_session_free(&session);
  MPI_T_finalize();
  MPI_Finalize();
  return 0;
}
