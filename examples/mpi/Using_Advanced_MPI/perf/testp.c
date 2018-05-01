#include "mpi.h"
/* A simple program to send and receive in an inefficient order */
#define MAX_REQ 128
void TestProgram(void)
{
    MPI_Request sr[MAX_REQ], rr[MAX_REQ];
    int wrank, wsize, i, from, to, err;

    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    from = 0;
    to   = wsize-1;

    if (wrank == from) {
	for (i=0; i<MAX_REQ; i++) {
	    MPI_Isend((void*)0, 0, MPI_BYTE, to,
                        i, MPI_COMM_WORLD, &sr[i]);
	}
    }
    MPI_Barrier(MPI_COMM_WORLD); /* To ensure that the sends are
                                    posted before the receives */
    if (wrank == to) {
	for (i=0; i<MAX_REQ; i++) {
	    MPI_Irecv((void*)0, 0, MPI_BYTE, from,
                       MAX_REQ-i-1, MPI_COMM_WORLD, &rr[i]);
	}
    }
    if (wrank == to) {
	MPI_Waitall(MAX_REQ, rr, MPI_STATUSES_IGNORE);
    }
    if (wrank == from) {
	MPI_Waitall(MAX_REQ, sr, MPI_STATUSES_IGNORE);
    }
}
