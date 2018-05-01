#include <stdio.h>
#include "mpi.h"
#include "nxtval.h"

void MPE_Counter_create(MPI_Comm old_comm, MPI_Comm *smaller_comm,
			MPI_Comm *counter_comm)
{
  int counter = 0;
  int message, done = 0, myid, numprocs, server, color;
  MPI_Status status;

  MPI_Comm_size(old_comm, &numprocs);
  MPI_Comm_rank(old_comm, &myid);
  server = numprocs-1;     /*   last proc is server */
  MPI_Comm_dup(old_comm, counter_comm); /* make one new comm */
  if (myid == server) color = MPI_UNDEFINED;
  else color = 0;
  MPI_Comm_split(old_comm, color, myid, smaller_comm);

  if (myid == server) {       /* I am the server */
    while (!done) {
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
                 MPI_ANY_TAG, *counter_comm, &status);
        if (status.MPI_TAG == REQUEST) {
            MPI_Send(&counter, 1, MPI_INT, status.MPI_SOURCE,
                     VALUE, *counter_comm);
            counter++;
        }
        else if (status.MPI_TAG == GOAWAY) {
            done = 1;
        }
        else {
            fprintf(stderr, "bad tag %d sent to MPE counter\n",
                    status.MPI_TAG);
    		MPI_Abort(*counter_comm, 1);
    	    }
    }
    MPE_Counter_free(smaller_comm, counter_comm);
  }
}
