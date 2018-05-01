/* Sequential execution code */
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  MPI_Comm lcomm;
  int      prevRank, nextRank;
} seqInfo;

static int seqKeyval = MPI_KEYVAL_INVALID;
