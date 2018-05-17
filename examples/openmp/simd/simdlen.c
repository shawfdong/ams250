/* Example of the simdlen clause on the simd construct

   The simdlen clause is a hint to guide the compiler in the selection
   of a vector length for the loop.
*/
unsigned int F(unsigned int *x, int n, unsigned int mask)
{
  #pragma omp simd simdlen(32/sizeof(unsigned int))
  for (int i=0; i<n; i++) {
    x[i] &= mask;
  } // End of simd region
}
