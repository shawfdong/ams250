/* Example of the reduction and collapse clauses on the simd construct

   The two perfectly nested loops are collapsed into a single iteration
   space. The reduction clause is required to parallelize the
   accumulation into t1.
*/
void simd_loop_collapse(double *r, double *b, double *c,
                        int n, int m)
{
  int i, j;
  double t1;

  t1 = 0.0;
  #pragma omp simd reduction(+:t1) collapse(2)
  for (i=0; i<n; i++)
    for (j=0; j<m; j++)
      t1 += func1(b[i], c[j]);
  *r = t1
}
