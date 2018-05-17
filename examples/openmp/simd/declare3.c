/* Example using the uniform and linear clauses for
   multidimension array access

   Access in the first dimension is uniform. The loop that calls
   the saxpy_2d() function indexes linearly through the second
   dimension via the variable j.
*/
#pragma omp declare simd uniform(x, y, d1, i, a) linear(j)
void saxpy_2d(float *x, float *y, float a, int d1, int i, int j)
{
  y[(d1*i)+j] = a*x[(d1*i)+j] + y[(d1*i)+j];
}
