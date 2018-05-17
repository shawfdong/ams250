/* Example of the safelen clause on the simd construct

   The safelen clause ensures that a vector length of up to 16
   is correct.
*/
void simd_loop_safelen(double *a, double *b, double *c, int n,
                       int offset)
{
  int i;
  
  #pragma omp simd safelen(16)
  for (i=offset; i<n; i++)
    a[i] = b[i-offset] + c[i];
}
