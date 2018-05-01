#include <stdio.h>
#include "mpi.h"
#include "ic_nxtval.h"

#define ICTAG 0
int MPE_Counter_create_ic(MPI_Comm oldcomm,
                          MPI_Comm *smaller_comm,
			  MPI_Comm *counter_comm)
{
  int counter = 0, message, done = 0, myid, numprocs, server;
  int color, remote_leader_rank;
  MPI_Status status;
  MPI_Comm oldcommdup, splitcomm;

  MPI_Comm_dup(oldcomm, &oldcommdup);
  MPI_Comm_size(oldcommdup, &numprocs);
  MPI_Comm_rank(oldcommdup, &myid);
  server = numprocs-1;       /* last proc is server */

  color = (myid == server);  /* split into server and rest */
  MPI_Comm_split(oldcomm, color, myid, &splitcomm);

  /* build intercommunicator using bridge w/ oldcommdup */
  if(!color) { /* I am not the server */
      /* 1) the non-server leader process is chosen to have rank
          "0" in the peer comm. oldcommdup != rank of server
          guaranteed that this leader "0" has rank "0" in both
        oldcommdup and in this splitcomm too, by virtue of
        MPI_Comm_split
         2) server has rank "server" in oldcommdup */

      remote_leader_rank = server; /* server rank, oldcommdup */
      *smaller_comm = splitcomm; /* return new, smaller world */
  }
  else {
      remote_leader_rank = 0; /* non-server leader, oldcommdup */
      *smaller_comm = MPI_COMM_NULL;
  }

  MPI_Intercomm_create(splitcomm, 0, oldcommdup,
                       remote_leader_rank, ICTAG, counter_comm);
  MPI_Comm_free(&oldcommdup); /* not needed after
                                 Intercomm_create */

  if (myid == server) {       /* I am the server */
    MPI_Comm_free(&splitcomm);
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
    MPI_Comm_free(counter_comm);
  }
  return 0;
}
