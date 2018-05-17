/* An ordered region within a SIMD loop

   The ordered region is executed with one SIMD lane in the
   original sequential order of the loop iterations.
*/
extern int x;
extern void global_update(int, int);
#pragma omp declare simd
extern int vec_work(int);

void F(int *a, int *b, int n)
{
  #pragma omp simd
  for (int i=0; i<n; i++)
  {
    // vectorize this part of the loop
    a[i] = vec_work(b[i]);

    // execute this part of the loop in sequential order
    #pragma omp ordered simd
    {
      global_update(x, a[i]);
    } // End ordered simd region
  } // End simd region
}
