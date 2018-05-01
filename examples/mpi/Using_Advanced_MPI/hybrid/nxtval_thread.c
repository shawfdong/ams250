#include "mpi.h"
#include <pthread.h>

#define EXIT_TAG 1
void *counter_routine(MPI_Comm *counterCommP)
{
 int incr, ival = 0;
 MPI_Status status;
 while (1) {
  MPI_Recv(&incr, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
           *counterCommP, &status);
  if (status.MPI_TAG == EXIT_TAG) return 0;
  MPI_Send(&ival, 1, MPI_INT, status.MPI_SOURCE, 0,
          *counterCommP);
  ival += incr;
 }
 return 0;
}
/* We discuss how to eliminate this global variable in the text */
static pthread_t thread_id;
void init_counter(MPI_Comm comm, MPI_Comm *counterCommP)
{
 int rank;
 MPI_Comm_dup_with_info(comm, MPI_INFO_NULL, counterCommP);
 MPI_Comm_rank(comm, &rank);
 if (rank == 0)
     pthread_create(&thread_id, NULL, (void*(*)(void *))counter_routine,
		    counterCommP);
}
/* Any process can call this to fetch and increment by val */
void counter_nxtval(MPI_Comm counter_comm, int incr, int *val)
{
 MPI_Send(&incr, 1, MPI_INT, 0, 0, counter_comm);
 MPI_Recv(val, 1, MPI_INT, 0, 0, counter_comm, MPI_STATUS_IGNORE);
}
/* Every process in counter_comm (including rank 0!) must call
   this */
void stop_counter(MPI_Comm *counterCommP)
{
 int rank;
 MPI_Barrier(*counterCommP);
 MPI_Comm_rank(*counterCommP, &rank);
 if (rank == 0) {
  MPI_Send(MPI_BOTTOM, 0, MPI_INT, 0, EXIT_TAG, *counterCommP);
  pthread_join(thread_id, NULL);
 }
 MPI_Comm_free(counterCommP);
}
