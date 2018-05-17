/* Example of the simd construct

   The vectors b and c are added and the result is stored in vector a
*/
void simd_loop(double *a, double *b, double *c, int n)
{
  int i;

  #pragma omp simd
  for (i=0; i<n; i++)
    a[i] = b[i] + c[i];
}
