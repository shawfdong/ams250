/* SIMD loops without and with the simd schedule modifier

   The simd schedule modifier in func_2() guarantees that a
   preferred implementation-defined vector length is respected
   when distributing the loop.
*/
void func_1(float *a, float *b, int n)
{
  #pragma omp for simd schedule(static, 5)
  for (int k=0; k<n; k++)
  {
    // do some work on a and b
  }
}

void func_2(float *a, float *b, int n)
{
  #pragma omp for simd schedule(simd:static, 5)
  for (int k=0; k<n; k++)
  {
    // do some work on a and b
  }
}
