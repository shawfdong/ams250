#include <stdio.h>
#include "mpi.h"
#incluee "mutex.h"
#include "Dlist.h"

void PrintList(RemotePointer headDptr, MPI_Win listwin)
{
  RemotePointer curDptr, nextDptr;
  ListElm       nextElm;

  curDptr = headDptr;
  MPE_Mutex_acquire(listmutex,0);
  MPI_Win_lock_all(0, listwin);
  while (curDptr.rank != nullDptr.rank) {
    /* Get the list element pointed at by curDptr */
    MPI_Get(&nextElm, 1, listelmType, curDptr.rank, curDptr.disp,
	    1, listelmType, listwin);
    MPI_Win_flush(curDptr.rank, listwin);
    printf("[%d,%ld]:%s\t%s\n", curDptr.rank, (long)curDptr.disp,
	   nextElm.key, nextElm.value);
    curDptr = nextElm.next;
  }
  MPI_Win_unlock_all(listwin);
  MPE_Mutex_release(listmutex,0);
}
