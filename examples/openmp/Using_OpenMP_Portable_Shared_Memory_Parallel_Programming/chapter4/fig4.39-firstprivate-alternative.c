/*

   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

   Copyright 2009 Sun Microsystems, Inc. All rights reserved.

   The contents of this file are subject to the terms of the BSD License("BSD")(the "License"). 
   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt

   The BSD License

   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:

       * Redistribution of source code must retain the above copyright 
         notice, this list of conditions and the following disclaimer.
       * Redistribution in binary form must reproduce the above copyright 
         notice, this list of conditions and the following disclaimer in 
         the documentation and/or other materials provided with the 
         distribution.
       * Neither the name of Sun Microsystems, Inc. or the names of 
         contributors may be used to endorse or promote products derived 
         from this software without specific prior written permission.

   This software is provided "AS IS," without a warranty of any kind. ALL 
   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY 
   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND 
   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A 
   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. 
   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT 
   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR 
   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS 
   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   You acknowledge that this software is not designed, licensed or intended for 
   use in the design, construction, operation or maintenance of any nuclear facility. 

*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
#endif

int main()
{
   int *a;
   int n = 2, nthreads, vlen, indx, offset = 4, i, TID;
   int failed;

#ifdef _OPENMP
   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(3);
#endif

   indx = offset;

   /*
   ------------------------------------------------------------------------
   Set up parameters for computation and allocate memory
   ------------------------------------------------------------------------
   */
   #pragma omp parallel firstprivate(indx) shared(a,n,nthreads,failed)
   {
     #pragma omp single
     {
        nthreads = omp_get_num_threads();
        vlen = indx + n*nthreads;
        if ( (a = (int *) malloc(vlen*sizeof(int))) == NULL )
           failed = TRUE;
        else
           failed = FALSE;
     }
   } /*-- End of parallel region --*/

   if ( failed == TRUE ) {
      printf("Fatal error: memory allocation for a failed vlen = %d\n",vlen);
      return(-1);
   }
   else
   {
      printf("Diagnostics:\n");
      printf("nthreads = %d\n",nthreads);
      printf("indx     = %d\n",indx);
      printf("n        = %d\n",n);
      printf("vlen     = %d\n",vlen);
   }

   for(i=0; i<vlen; i++) a[i] = -i-1;

   /*
   ------------------------------------------------------------------------
   Each thread starts access to array a through variable offset
   ------------------------------------------------------------------------
   */
   printf("Length of segment per thread is %d\n",n);
   printf("Offset for vector a is %d\n",indx);
   #pragma omp parallel default(none) private(i,TID,indx) \
           shared(n,offset,a)
   {
      TID = omp_get_thread_num();
      indx = offset + n*TID;
      for(i=indx; i<indx+n; i++)
         a[i] = TID + 1;
   } /*-- End of parallel region --*/

   printf("After the parallel region:\n");
   for (i=0; i<vlen; i++)
      printf("a[%d] = %d\n",i,a[i]);

   free(a);

   return(0);
}
