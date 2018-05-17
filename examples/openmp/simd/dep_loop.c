/* Example of a loop-carried dependence

   The loop-carried dependence creates a limit on the vector length.
*/
void dep_loop(float *a, float c, int n)
{
  for (int i=8; i<n; i++)
    a[i] = a[i-8] * c;
}
