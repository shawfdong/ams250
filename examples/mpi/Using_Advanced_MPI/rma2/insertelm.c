#include "mpi.h"
#include "mutex.h"
#include "Dlist.h"
#include <string.h>

int InsertElm(RemotePointer headDptr,
              const char *key, const char *value,
              MPI_Win listwin)
{
  RemotePointer dptr, last_dptr, new_dptr;
  int           compare;
  ListElm       elmOfptr, *new_lptr;
  int           *attrval, myrank, flag;


  MPI_Win_get_attr(listwin, MPE_LISTWIN_KEY_RANK, &attrval,
                   &flag);
  if (!flag) {
    /* Listwin not properly initialized */
    return 1;
  }
  myrank = (int)(MPI_Aint)attrval;  /* We store the rank in the
                                       attrval, which is an
                                       address-sized value */

  MPE_Mutex_acquire(listmutex,0);

  last_dptr = headDptr;
  MPI_Win_lock_all(0, listwin);
  MPI_Get(&dptr, 1, dptrType, last_dptr.rank,
    DispInListElm(last_dptr,next), 1, dptrType, listwin );
  MPI_Win_flush(last_dptr.rank, listwin);

  while (dptr.rank != nullDptr.rank) {
    MPI_Get(&elmOfptr, 1, listelmType, dptr.rank, dptr.disp,
	    1, listelmType, listwin);
    MPI_Win_flush(dptr.rank, listwin);
    /* elm is what ptr points to (i.e., *ptr) */
    compare = strcmp(elmOfptr.key, key);
    if (compare == 0) {
      /* Duplicate key.  Ignore */
      MPI_Win_unlock_all(listwin);
      return 0;
    }
    if (compare > 0) break; /* Insert in front of this */
    last_dptr = dptr;
    dptr      = elmOfptr.next; /* i.e., ptr->next */
  }

  /* Create new element */
  MPI_Alloc_mem(sizeof(ListElm), MPI_INFO_NULL, &new_lptr);
  strncpy(new_lptr->key, key, MAX_KEY_SIZE);
  strncpy(new_lptr->value, value, MAX_VALUE_SIZE);
  new_lptr->next = dptr;
  MPI_Win_attach(listwin, new_lptr, sizeof(ListElm));

  new_dptr.rank = myrank;
  MPI_Get_address(new_lptr,&new_dptr.disp);
  MPI_Put(&new_dptr, 1, dptrType, last_dptr.rank, 
      DispInListElm(last_dptr,next), 1, dptrType,
	    listwin);
  MPI_Win_unlock_all(listwin);
  MPE_Mutex_release(listmutex,0);
  return 0;
}
