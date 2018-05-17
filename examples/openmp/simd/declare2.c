/* Example of the linear and uniform clauses on the
   declare simd directive

   The SIMD variant of the cosScaled function may assume that ptr
   and scale are loop invariant and that idx is incremented by 1
   each time through the loop from where the function is called.
*/
#include <math.h>
#pragma omp declare simd uniform(ptr, scale) linear(idx:1)
double cosScaled(double *ptr, double scale, int idx)
{
  return (cos(ptr[idx]) * scale);
}

void simd_loop_uniform_linear(double *a, double *b, double c,
                              int n)
{
  int i;

  #pragma omp simd
  for (int i=0; i<n; i++) {
    a[i] = cosScaled(b, c, i);
  }
  // End simd region
}
