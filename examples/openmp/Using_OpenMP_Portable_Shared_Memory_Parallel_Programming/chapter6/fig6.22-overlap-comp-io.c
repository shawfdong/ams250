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
#include <string.h>
#include <float.h>
#include <malloc.h>
#include <unistd.h>

#include <time.h>

#define TRUE  1
#define FALSE 0

#define FABS(x) (x < 0 ? -x : x)

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

int DefValN = 6;
int DefValM = 10;

char file_read[] = "fig6.22-file-io.bin";

enum STATUS {UNDEFINED, READ_IN_PROGRESS, READ_FINISHED, 
             PROCESSING_IN_PROGRESS, PROCESSING_FINISHED} *execution_state;

void read_input(int i);
void signal_read(int i);
void wait_read(int i);
void process_data(int i);
void signal_processed(int i);
void wait_processed(int i);
void write_output(int i);
void do_compute(int i,int j);

void get_cmd_line_options(int, char **);
void init_memory();
void init_data();
void generate_input_file();
void compute_reference_results();
void print_header();
int check_results();
void print_state_array(int, char *, int);

double *a, *b, **c, **ref;

FILE *fp_write;

int verbose;
int N, M;

int main(int argc, char **argv)
{

   int error_count;

/*
   ------------------------------------------------------------
   This program runs fine using one thread, but if we do 
   execute in parallel, at least 3 threads are needed.
   ------------------------------------------------------------
*/
#ifdef _OPENMP
   int thread_count_error;

   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(3);

   (void) omp_set_nested(TRUE);
   if (! omp_get_nested()) {printf("Warning: nested parallelism not set\n");}

   #pragma omp parallel shared(thread_count_error)
   {
       #pragma omp single
       {
         if ( omp_get_num_threads() < 3 ) {
            printf("Fatal error - At least 3 threads are needed, but only %d available\n",
                   omp_get_num_threads());
            thread_count_error = TRUE;
         } else {
            thread_count_error = FALSE;
         }
       }
      
   } /*-- End of parallel region --*/

   if ( thread_count_error == TRUE ) return(-1);
#endif
 
/*
   ------------------------------------------------------------
   Initial, serial, phase. Get the command line options, 
   allocate memory, initialize data, generate input file
   and print the header.
   ------------------------------------------------------------
*/
   (void) get_cmd_line_options(argc,argv);

   if (verbose) printf("Allocating memory for data structures\n");

   (void) init_memory();

   if (verbose) printf("Memory for data structures allocated\n");

   if (verbose) printf("Initializing data structures\n");

   (void) init_data();

   if (verbose) printf("Data structures initialized\n");

   (void) generate_input_file();

   (void) compute_reference_results();

   (void) print_header();

/*
   ------------------------------------------------------------
   This implements the pipeline, overlapping I/O and 
   computations. Each section block handles a specific phase.
   ------------------------------------------------------------
*/

#pragma omp parallel sections
{
   #pragma omp section
   {
     if (verbose) printf("TID = %d - in main: performs the read operations\n",omp_get_thread_num());

     for (int i=0; i<N; i++) {
        (void) read_input(i);
        (void) signal_read(i);
     }
   }
   #pragma omp section
   {
     if (verbose) printf("TID = %d - in main: performs the computations\n",omp_get_thread_num());
     for (int i=0; i<N; i++) {
        (void) wait_read(i);
        (void) process_data(i);
        (void) signal_processed(i);
     }
   }
   #pragma omp section
   {
     if (verbose) printf("TID = %d - in main: performs the write operations\n",omp_get_thread_num());
     for (int i=0; i<N; i++) {
        (void) wait_processed(i);
        (void) write_output(i);
     }
   }
} /*-- End of parallel sections --*/

  if ( (error_count = check_results()) == 0 ) {
     printf("Program executed successfully\n");
  } else {
     printf("FATAL ERROR: found %d differences in the result(s)\n",error_count);
  }

  free(a);
  free(b);
  free(c);
  free(ref);
  free(execution_state);

  return(0);

} /*-- End of main program --*/

void read_input(int i)
{
   FILE *fp_read;

   execution_state[i] = READ_IN_PROGRESS;

   #pragma omp flush

   print_state_array(omp_get_thread_num(),"read_input",i);

   /*
      ------------------------------------------------------------
      Note that this is clumsy by design in order to get some
      time spent in the I/O part. 
      ------------------------------------------------------------
   */

   if ( (fp_read = fopen(file_read,"r")) != NULL ) {
         if ( fseek(fp_read,(long) i*2*sizeof(double), SEEK_SET) == 0 ) {
            if ( fread(&a[i],sizeof(double),1,fp_read) != 1 ) {
               perror("read_input: array a"); exit(1);
            }
            if ( fread(&b[i],sizeof(double),1,fp_read) != 1 ) {
               perror("read_input: array b"); exit(1);
            }
            if (verbose) {
               printf("TID = %d - in read_input: a[%d]=%f b[%d]=%f\n",
                      omp_get_thread_num(),i,a[i],i,b[i]);
            }
         } else {
           perror("read_input: seek error"); exit(1);
         }
      fclose(fp_read);
   } else {
     perror("read_input: open file for read");
   }

} /*-- End of read_input --*/

void signal_read(int i)
{
   print_state_array(omp_get_thread_num(),"signal_read",i);

   execution_state[i] = READ_FINISHED; 

   #pragma omp flush

   print_state_array(omp_get_thread_num(),"signal_read",i);

} /*-- End of signal_read --*/

void wait_read(int i)
{

   print_state_array(omp_get_thread_num(),"wait_read",i);

   #pragma omp flush

   while ( execution_state[i] != READ_FINISHED )
   {
      print_state_array(omp_get_thread_num(),"wait_read",i);

      system("sleep 1");

      #pragma omp flush
   }
   print_state_array(omp_get_thread_num(),"wait_read",i);

} /*-- End of wait_read --*/

void process_data(int i)
{
   int TID_LVL_1 = omp_get_thread_num();

   execution_state[i] = PROCESSING_IN_PROGRESS;

   #pragma omp flush

   print_state_array(TID_LVL_1,"process_data",i);

   #pragma omp parallel for num_threads(4)
   for (int j=0 ; j<M; j++) {
       if (verbose) printf("TID:subTID = %d:%d - in process_data: iteration j=%d\n",
                           TID_LVL_1,omp_get_thread_num(),j);
       do_compute(i,j);
   }

} /*-- End of process_data --*/

void do_compute(int i,int j)
{

   c[i][j] += a[i] + b[i];

   if (verbose) {
      printf("\tin do_compute: updated c[%d][%d]\n",i,j);
   }

} /*-- End of do_compute --*/


void signal_processed(int i)
{
   execution_state[i] = PROCESSING_FINISHED; 

   #pragma omp flush

   print_state_array(omp_get_thread_num(),"signal_processed",i);

} /*-- End of signal_processed --*/

void wait_processed(int i)
{

   print_state_array(omp_get_thread_num(),"wait_processed",i);

   #pragma omp flush

   while ( execution_state[i] != PROCESSING_FINISHED )
   {
      print_state_array(omp_get_thread_num(),"wait_processed",i);

      system("sleep 1");

      #pragma omp flush
   }

   print_state_array(omp_get_thread_num(),"wait_processed",i);

} /*-- End of wait_processed --*/

void write_output(int i)
{
   int CutOffPrint = 9; /*-- Limits number of values printed --*/

   print_state_array(omp_get_thread_num(),"write_output",i);

   if (verbose) {
      printf("TID = %d - in write_output: i=%d\n",omp_get_thread_num(),i);

      printf("\tc[%d][]: ",i);
      if ( M < CutOffPrint ) {
         for (int j=0; j<M; j++)
            printf("%.2f ",c[i][j]);
      } else {
         for (int j=0; j<CutOffPrint; j++)
            printf("%.2f ",c[i][j]);
         printf("... %.2f ",c[i][M-1]);
      }
      printf("\n");
   }
   
} /*-- End of write_output --*/

void generate_input_file()
{
   if ( (fp_write = fopen(file_read,"w")) != NULL ) {
      for(int i=0; i<N; i++)
      {
         fwrite(&a[i],sizeof(double),1,fp_write);
         fwrite(&b[i],sizeof(double),1,fp_write);
      }
      fclose(fp_write);
   } else {
     perror("generate_input_file: open file for write"); exit(1);
   }

} /*-- End of generate_input --*/

void compute_reference_results()
{
   for (int i=0; i<N; i++)
      for (int j=0; j<M; j++)
          ref[i][j] = 0.0;

   for (int i=0; i<N; i++)
      for (int j=0; j<M; j++)
          ref[i][j] += a[i] + b[i];

} /*-- End of compute_reference_results --*/

int check_results()
{
   double rel_error;
   double TOL = DBL_EPSILON*10.0;
   int error_count = 0;

   for (int i=0; i<N; i++)
      for (int j=0; j<M; j++)
      {
          if (FABS(ref[i][j]) > DBL_MAX)
             rel_error = FABS( (c[i][j] - ref[i][j])/ref[i][j] );
          else
             rel_error = FABS( c[i][j] - ref[i][j] );

          if (rel_error > TOL ) {
             error_count++;
             printf("c[%d][%d] = %f ref[%d][%d] = %f rel. error = %e\n",
                    i,j,c[i][j],i,j,ref[i][j],rel_error);
          }
      }
   return(error_count);

} /*-- End of check_results --*/

void init_memory()
{
   if ( (a = (double *) malloc(N*sizeof(double))) == NULL ) {
     perror("init_memory: memory allocation failure for a"); exit(1);
   } else {
     if (verbose) printf("\tAllocated memory for a\n");
   }

   if ( (b = (double *) malloc(N*sizeof(double))) == NULL ) {
     perror("init_memory: memory allocation failure for b"); exit(1);
   } else {
     if (verbose) printf("\tAllocated memory for b\n");
   }

   if ( (c = (double **) malloc(N*sizeof(double))) == NULL ) {
     perror("init_memory: memory allocation failure for c"); exit(1);
   } else {
     for (int i=0; i<N; i++)
       if ( (c[i] = malloc(M*sizeof(double))) == NULL ) {
          perror("init_memory: memory allocation failure for c"); exit(1);
       } 
   }
   if (verbose) printf("\tAllocated memory for c\n");

   if ( (ref = (double **) malloc(N*sizeof(double))) == NULL ) {
     perror("init_memory: memory allocation failure for ref"); exit(1);
   } else {
     for (int i=0; i<N; i++)
       if ( (ref[i] = malloc(M*sizeof(double))) == NULL ) {
          perror("init_memory: memory allocation failure for ref"); exit(1);
       } 
   }
   if (verbose) printf("\tAllocated memory for ref\n");
       
   if ( (execution_state = malloc(N*sizeof(int))) == NULL ) {
     perror("init_memory: memory allocation failure for execution_state"); exit(1);
   } else {
     if (verbose) printf("\tAllocated memory for execution_state\n");
   }

} /*-- End of init_memory --*/

void init_data()
{
   for (int i=0; i<N; i++) 
      a[i] = i+1;

   for (int i=0; i<N; i++) 
      b[i] = a[N-1] + i+1;

   for (int i=0; i<N; i++)
      for (int j=0; j<M; j++)
          c[i][j] = 0.0;

   for (int i=0; i<N; i++)
      execution_state[i] = UNDEFINED;
   #pragma omp flush

} /*-- End of init_data --*/

void get_cmd_line_options(int argc, char **argv)
{
   char optstring[]="N:M:hv";

   int         c;
   extern char *optarg;
   extern int  opterr;

   N       = DefValN;
   M       = DefValM;
   verbose = FALSE;

   if ( argc > 1 ) {
      opterr = 0;  
      while ((c = getopt(argc, argv, optstring)) != EOF)
        {
            switch (c) {
            case 'N':
               N = atoi(optarg);
               break;
            case 'M':
               M = atoi(optarg);
               break;
            case 'v':
               verbose = TRUE;
               break;
            case 'h':
               printf("Usage:%s [-N <n>] [-M <m>] [-v] [-h]\n\n",argv[0]);
               printf("Options supported:\n");
               printf("  <N> problem size (optional - default is %d)\n",DefValN);
               printf("  <M> problem size (optional - default is %d)\n",DefValM);
               printf("  <v> activates verbose mode (optional- by default it is off)\n");
               printf("  <h> display this usage overview\n");
               exit(0);
               break;
            case '?':
               printf("Warning: incomplete or incorrect option(s) ignored\n");
               break;

            } /*-- End of switch over options --*/

      } /*-- End of while --*/

   } /*-- End of if over argc --*/

   if (verbose) printf("N=%d M=%d\n",N,M);
   return;

} /*-- End of get_cmd_line_options --*/

void print_state_array(int TID, char *name, int i)
{
   static int first = TRUE;

   #pragma omp critical
   {
      if (first) {
         first = FALSE;

         #pragma omp flush

         printf("Thread ID  Function             Execution Status Array\n");
         printf("                    Value of i:");
         for (int j=0; j<N; j++) printf("%3d",j);
         printf("\n\n");
      }

      printf("%6d     %-20s",TID,name);

      if ( i >= 0 )
      {
         for (int j=0; j<i; j++) {

             #pragma omp flush
             printf(" %2d",execution_state[j]);
          }
          #pragma omp flush
          printf(" *%1d",execution_state[i]);
      }

      for (int j=i+1; j<N; j++) {

          #pragma omp flush
          printf(" %2d",execution_state[j]);
      }
      printf("\n");
   } /*-- End of critical section --*/

   return;

} /*-- End of print_state_array --*/

void print_header()
{
   printf("This program demonstrates how I/O can be overlapped with computations.\n");
   printf("Several options are supported. Use the -h option for an overview.\n");
   printf("\n");
   printf("There are 3 distinct phases. Each phase is assigned to a different thread.\n");
   printf("Correct execution is independent of the assignment of a phase to a specific thread.\n");
   printf("\n");
   printf("These are the different phases:\n");
   printf("Input         phase: read_input     - signal_read\n");
   printf("Computational phase: wait_read      - process_data - signal_processed\n");
   printf("Output        phase: wait_processed - write_output\n");
   printf("\n");
   printf("The entire operation is splitted into chunks. A specific chunk is represented\n");
   printf("by the value of iteration i. In total there are %d chunks\n",N);
   printf("\n");

   printf("An internal status flag is used to pass on information between the threads\n");
   printf("regarding a specific phase.\n");
   printf("\n");
   printf("Legend for status flag\n");
   printf("\t%d - UNDEFINED\n"             ,UNDEFINED);
   printf("\t%d - READ_IN_PROGRESS\n"      ,READ_IN_PROGRESS);
   printf("\t%d - READ_FINISHED\n"         ,READ_FINISHED);
   printf("\t%d - PROCESSING_IN_PROGRESS\n",PROCESSING_IN_PROGRESS);
   printf("\t%d - PROCESSING_FINISHED\n"   ,PROCESSING_FINISHED);
   printf("\n");
   printf("The table below displays what function a specific thread is executing,\n");
   printf("as well as the value of the status flag for a values of i.\n");
   printf("\n");

   printf("The * symbol indicates the current value of i the function is working on\n");
   printf("\n");

   print_state_array(omp_get_thread_num(),"initialization",-1);

} /*-- End of print_header --*/
