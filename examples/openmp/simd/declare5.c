/* Example of the aligned clause on the declare simd directive

   Use the aligned clauses on the declare simd directive to
   generate SIMD variants of the functions copy32x8(),
   and saxpy() that expect the addresses passed in pointer
   arguments to have a specific byte alignment.
*/
#pragma omp declare simd linear(src,dst) \
                         aligned(src,dst:16) simdlen(32)
void copy32x8(char *dst, char *src)
{
  *dst = *src;
}

#pragma omp declare simd uniform(x,y) linear(i) \
                         aligned(x,y:64) simdlen(16)
float saxpy(float a, float *x, float *y, int i)
{
  return a * ((x[i]) + (y[i]));
}
