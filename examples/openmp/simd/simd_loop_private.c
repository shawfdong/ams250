/* Example using private variables in a simd construct

   The two function calls return intermediate results that must be
   stored in private variables to avoid a data race. Each SIMD lane
   has its own instance of a private variable.
*/
void simd_loop_private(double *a, double *b, double *c, int n)
{
  int i;
  double t1, t2;

  #pragma omp simd private(t1, t2)
  for (i=0; i<n; i++)
  {
    t1 = func1(b[i], c[i]);
    t2 = func2(b[i], c[i]);
    a[i] = b[i] + c[i];
  }
}
