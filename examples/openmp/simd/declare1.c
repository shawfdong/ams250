/* Example of the declare simd directive

   The function my_func() is called from within a simd construct.
   The declare simd directive declares that the compiler should
   generate a SIMD version of the function.
*/
#pragma omp declare simd
double my_func(double b, double c)
{
  double r;
  r = b + c;
  return r;
}

void simd_loop_function(double *a, double *b, double *c, int n)
{
  int i;
  #pragma omp simd
  for (i=0; i<n; i += 2)
  {
    a[i] = my_func(b[i], c[i]);
  }
  // End simd region
}
