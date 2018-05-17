/* Example that uses the composite for simd construct

   The numerical solution for integration has a compute-intensive
   loop that is parallelized and vectorized.
*/
double compute_pi(int n)
{
  const double dH = 1.0 / (double) n;
  double dX, dSum = 0.0;

  #pragma omp parallel for simd private(dX) \
                       reduction(+:dSum) schedule(simd:static)
  for (int i=0; i<n; i++) {
    dX = dH * ((double) i + 0.5);
    dSum += (4.0 / (1.0 + dX * dX));
  } // End parallel for simd region

  return dH * dSum;
}
