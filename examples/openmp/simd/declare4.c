/* Example of the simdlen clause on the declare simd directive

   Use the simdlen clauses on the declare simd directive to
   generate a SIMD variant of the function F() that has a
   vector length of 16.
*/
#pragma omp declare simd simdlen(16)
char F(char x, char y, unsigned char mask)
{
  return (x + y) & mask;
}

void img_mask(char *img1, char *img2, int n, unsigned char *m)
{
  #pragma omp simd simdlen(16)
  for (int i=0; i<n; i++) {
    img1[i] = F(img1[i], img2[i], m[i]);
  } // End simd region
}
