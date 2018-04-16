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

#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
  #include <omp.h>
  #define TRUE  1
  #define FALSE 0
#endif

int main()
{
  int n = 4;
  int *a, **b;

#ifdef _OPENMP
   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(4);
#endif

  if ( (a=(int *)malloc(n*sizeof(int))) == NULL ) {
      perror("array a"); exit(-1);
  }

  if ( (b=(int **)malloc(n*sizeof(int *))) == NULL ) {
      perror("array b"); exit(-1);
  } 
  else {
      for (int i=0; i<n; i++)
          if ( (b[i]=(int *)malloc(n*sizeof(int))) == NULL )
             {perror("array b"); exit(-1);}
  }
 
  #pragma omp parallel shared(n,a,b)
  {
    #pragma omp for
    for (int i=0; i<n; i++)
    {
        a[i] = i + 1;
        #pragma omp parallel for /*-- Okay - This is a parallel region --*/
        for (int j=0; j<n; j++)
            b[i][j] = a[i];
    }
  } /*-- End of parallel region --*/

  for (int i=0; i<n; i++)
  {
      for (int j=0; j<n; j++)
         printf("b[%d][%d] = %d ",i,j,b[i][j]);
      printf("\n");
  }

  free(a);
  free(b);
}
