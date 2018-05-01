/* Sequential execution code */
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

static int verbose = 0;

typedef struct {
  MPI_Comm lcomm;
  int      prevRank, nextRank;
} seqInfo;

static int seqKeyval = MPI_KEYVAL_INVALID;

static int seqDelFn( MPI_Comm comm, int keyval, void *attr, void *estate )
{
  seqInfo *myinfo = (seqInfo *)attr;
  if (verbose) printf( "About to free communicator %d\n", myinfo->lcomm );

  MPI_Comm_free( &myinfo->lcomm );
  free( myinfo );
  return 0;
}

#if 0
/* This is an option to explain the copy function */
static int seqCopyFn( MPI_Comm comm, int keyval, void *attr, void *estate )
{
  seqInfo *myinfo = (seqInfo *)attr;
  /* preload the duplicated communicator */

  return 0;
}
#endif

void seqBegin( MPI_Comm comm )
{
  MPI_Comm lcomm;
  int      flag, mysize, myrank;
  seqInfo  *info;
  if (seqKeyval == MPI_KEYVAL_INVALID) {
    MPI_Comm_create_keyval( MPI_NULL_COPY_FN, seqDelFn, &seqKeyval, NULL );
  }
  MPI_Comm_get_attr( comm, seqKeyval, &info, &flag );
  if (!flag) {
    info = (seqInfo *)malloc( sizeof(seqInfo) );
    MPI_Comm_dup( comm, &info->lcomm );
    MPI_Comm_rank( info->lcomm, &myrank );
    MPI_Comm_size( info->lcomm, &mysize );
    info->prevRank = myrank - 1;
    if (info->prevRank < 0)   info->prevRank = MPI_PROC_NULL;
    info->nextRank = myrank + 1;
    if (info->nextRank >= mysize) info->nextRank = MPI_PROC_NULL;
    if (verbose) {
      printf( "seqbegin: prev = %d, next = %d\n",
	      info->prevRank, info->nextRank );
    }
    MPI_Comm_set_attr( comm, seqKeyval, info );
  }
  MPI_Recv( NULL, 0, MPI_INT, info->prevRank, 0, info->lcomm,
	    MPI_STATUS_IGNORE );
}

void seqEnd( MPI_Comm comm )
{
  seqInfo *info;
  int     flag;

  /* Sanity check */
  if (seqKeyval == MPI_KEYVAL_INVALID)
    MPI_Abort( MPI_COMM_WORLD, 1 );
  MPI_Comm_get_attr( comm, seqKeyval, &info, &flag );
  if (!info || !flag)
    MPI_Abort( MPI_COMM_WORLD, 1 );
  if (verbose) {
    printf( "seqend: prev = %d, next = %d\n",
	    info->prevRank, info->nextRank );
  }
  MPI_Send( NULL, 0, MPI_INT, info->nextRank, 0, info->lcomm );

  /* Make everyone wait until all have completed their send */
  MPI_Barrier( info->lcomm );
}

/* The process with prev == MPI_PROC_NULL goes first */
void seqChangeOrder( MPI_Comm comm, int prev, int next )
{
  seqInfo *info;
  int flag;
  /* Sanity check */
  if (seqKeyval == MPI_KEYVAL_INVALID)
    MPI_Abort( MPI_COMM_WORLD, 1 );
  MPI_Comm_get_attr( comm, seqKeyval, &info, &flag );
  if (!info || !flag)
    MPI_Abort( MPI_COMM_WORLD, 1 );
  /* Update the order */
  info->prevRank = prev;
  info->nextRank = next;
}
