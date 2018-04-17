/* OpenMP TASK Example: Computing Fibonacci Numbers */
#include <stdio.h>
#include <omp.h>

int *value, *done;
omp_lock_t *dolock;

int fib(int n) {
  int i, j;
  if (n<2)
    return n;
  else {
    omp_set_lock( &(dolock[n]) );
    if (!done[n]) {
      #pragma omp task shared(i) firstprivate(n)
      i=fib(n-1);
      #pragma omp task shared(j) firstprivate(n)
      j=fib(n-2);
      #pragma omp taskwait
      value[n] = i+j;
      done[n] = 1;
    }
    omp_unset_lock( &(dolock[n]) );
    return value[n];
  }
}

int main() {
  int n = 10;
  value = (int *) malloc( n*sizeof(int) );
  done = (int *) malloc( n*sizeof(int) );
  dolock = (omp_lock_t *) malloc(n * sizeof(omp_lock-t));

  #pragma omp parallel shared(n)
  {
    #pragma omp single
    printf ("fib(%d) = %d\n", n, fib(n));
  }

  free(value);
  free(done);
  free(dolock);

  return 0;
}
