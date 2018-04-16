/* critical Directive Example */
#include <omp.h>

main(int argc, char *argv[]) {

  int x;
  x = 0;

  #pragma omp parallel shared(x)
  {
  
    #pragma omp critical
    x = x + 1;

  }  /* end of parallel region */

}
