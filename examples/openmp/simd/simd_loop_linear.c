/* Example of the linear clause on the simd construct

   The linear clause defines how the j index variable relates to the
   loop variable i that is used as an index into some of the arrays.
*/
void simd_loop_linear(double *a, double *b, double *c, int n,
                       int offset)
{
  int i, j = 0;

  #pragma omp simd linear(j:1)
  for (i=offset; i<n; i+=2)
    a[i] = b[j++] + c[i];
}
