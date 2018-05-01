#include "mpi.h"

int MPE_Safe_comm_dup(MPI_Comm comm, MPI_Comm *newcomm)
{
   MPI_Info oldinfo, myinfo;
   char value[MPI_MAX_INFO_VAL];
   int  flag, err;

   MPI_Info_create(&myinfo);
   MPI_Comm_get_info(comm, &oldinfo);
   /* Look for the one info key we want to propagate to
      the new communicator */
   MPI_Info_get(oldinfo, "commfast", sizeof(value),
                value, &flag);
   if (flag)
      MPI_Info_set(myinfo, "commfast", value);
   err = MPI_Comm_dup_with_info(comm, myinfo, newcomm);
   MPI_Info_free(&myinfo);
   MPI_Info_free(&oldinfo);
   return err;
}
