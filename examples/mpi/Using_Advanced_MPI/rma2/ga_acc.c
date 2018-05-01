#include "ga.h"
int ga_acc(GA ga, int ilo, int ihigh, int jlo, int jhigh,
           void *buf)
{
 int      jcur, jfirst, jlast, j, rank, rank_first, rank_last;
 MPI_Aint disp;

 /* In order to ensure that the entire update is atomic, we must
    first mutex-lock all of the windows that we will access */
 rank_first = (jlo - 1) / ga->chunk2;
 rank_last  = (jhigh - 1) / ga->chunk2;
 for (rank = rank_first; rank <= rank_last; rank++) {
     MPE_Mutex_acquire(ga->lock_win, rank);
 }

 jcur = jlo;
 while (jcur <= jhigh) {
   rank   = (jcur - 1) /ga->chunk2;
   jfirst = rank * ga->chunk2 + 1;
   jlast  = (rank + 1) * ga->chunk2;
   if (jlast > jhigh) jlast = jhigh;

   MPI_Win_lock(MPI_LOCK_SHARED, rank, MPI_MODE_NOCHECK,
                ga->ga_win);
   for (j=jcur; j<=jlast; j++) {
       disp = (j - jfirst) * ga->dim1 + (ilo - 1);
       MPI_Accumulate(buf, ihigh - ilo + 1, ga->dtype,
                      rank, disp, ihigh - ilo + 1, ga->dtype,
                      MPI_SUM, ga->ga_win);
       buf = (void *)( ((char *)buf) +
                      (ihigh - ilo + 1) *  ga->dtype_size);
   }
   MPI_Win_unlock(rank, ga->ga_win);

   MPE_Mutex_release(ga->lock_win, rank);
   jcur = jlast + 1;
 }
 return 0;
}

