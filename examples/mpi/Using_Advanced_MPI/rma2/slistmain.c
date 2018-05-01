#include <stdio.h>
#include "mpi.h"
#include "Dlist.h"

MPI_Win listmutex;
static RemotePointer headDptr = {0,-1,0};
RemotePointer nullDptr = {0,-1,0};
MPI_Datatype listelmType, dptrType;
int MPE_LISTWIN_KEY_RANK = MPI_KEYVAL_INVALID;

int main(int argc, char **argv)
{
  int      wrank, i;
  MPI_Win  listwin;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &wrank);

  /* Initialize: the mutex, datatype, window, and list head  */
  MPE_Mutex_create(&listmutex);

  {
  int      blens[3];
  MPI_Aint displ[3];
  MPI_Datatype dtypes[3];
  ListElm  sampleElm;

  blens[0] = 1; blens[1] = 1;
  MPI_Get_address( &nullDptr.disp, &displ[0] );
  MPI_Get_address( &nullDptr.rank, &displ[1] );
  displ[1] = displ[1] - displ[0];
  displ[0] = 0;
  dtypes[0] = MPI_AINT;
  dtypes[1] = MPI_INT;
  MPI_Type_create_struct(2, blens, displ, dtypes, &dptrType);
  MPI_Type_commit(&dptrType);

  blens[0] = 1;              dtypes[0] = dptrType;
  blens[1] = MAX_KEY_SIZE;   dtypes[1] = MPI_CHAR;
  blens[2] = MAX_VALUE_SIZE; dtypes[2] = MPI_CHAR;
  MPI_Get_address(&sampleElm.next,&displ[0]);
  MPI_Get_address(&sampleElm.key[0],&displ[1]);
  MPI_Get_address(&sampleElm.value[0],&displ[2]);
  displ[2] -= displ[0];
  displ[1] -= displ[0];
  displ[0] = 0;
  for (i=0; i<3; i++) {
    printf("%d:count=%d,disp=%ld\n",i, blens[i], displ[i]);
  }
  MPI_Type_create_struct(3, blens, displ, dtypes, &listelmType);
  /* MPI_Type_contiguous(sizeof(ListElm), MPI_BYTE, &listelmType);*/
  MPI_Type_commit(&listelmType);
  }

  MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &listwin);

  MPI_Win_create_keyval(MPI_WIN_NULL_COPY_FN, MPI_WIN_NULL_DELETE_FN,
			&MPE_LISTWIN_KEY_RANK, (void*)0);
  MPI_Win_set_attr(listwin, MPE_LISTWIN_KEY_RANK, (void*)(MPI_Aint)wrank);

  headDptr.rank = 0;
  if (wrank == 0) {
    ListElm *headLptr;
    MPI_Alloc_mem(sizeof(ListElm), MPI_INFO_NULL, &headLptr);
    MPI_Get_address(headLptr,&headDptr.disp);
    headLptr->next.rank = -1;
    headLptr->next.disp = (MPI_Aint)MPI_BOTTOM;
    MPI_Win_attach(listwin, headLptr, sizeof(ListElm));
  }
  MPI_Bcast(&headDptr.disp, 1, MPI_AINT, 0, MPI_COMM_WORLD);

  /* Have each process insert some random strings */
  for (i=0; i<3; i++) {
    char key[MAX_KEY_SIZE], value[MAX_VALUE_SIZE];
    sprintf(key,"key%03d-%03d", wrank, i );
    sprintf(value,"value-%0d3-%03d", wrank, i );
    InsertElm(headDptr, key, value, listwin);
  }

  /* Ensure that everyone has finished */
  MPI_Barrier(MPI_COMM_WORLD);

  /* Print out the list */
  if (wrank == 0) {
    PrintList(headDptr, listwin);
  }

  MPI_Finalize();
  return 0;
}

/* Utility routine */
void printDptr(const char *msg, RemotePointer dptr)
{
  printf("%s<%d,%ld>\n", msg, dptr.rank, (long)dptr.disp);
}
