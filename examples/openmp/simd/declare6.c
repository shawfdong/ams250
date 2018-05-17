/* Example of the ref and uval modifiers in the linear clause

   The ref modifier declares that the address of x is linear.
   The uval modifier declares that the address of c is uniform,
   and its value is linear.
*/
#pragma omp declare simd linear(ref(x)) linear(uval(c))
void increment(int& x, int& c)
{ x += c; }

void Fref(int *a, int n)
{
  #pragma omp simd
  for (int i=0; i<n; i++) {
    increment(a[i], i);
  } // End simd region
}
