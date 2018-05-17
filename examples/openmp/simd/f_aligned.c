/* Example of the aligned clause on the simd construct

   The aligned clause asserts that the value of the pointer
   variable x is always aligned on a 16 byte boundary.
   With this information, the compiler may generate wider and
   more efficient vector load and store instructions.
*/
void f_aligned(float *x, float scale, int n)
{
  int i;

  #pragma omp simd aligned(x:16)
  for (i=0; i<n; i++)
    x[i] = x[i]*scale;
}
