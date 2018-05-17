/* Example of the inbranch and notinbranch clauses on the
   declare simd directive

   The inbranch clause tells the compiler to generate a SIMD
   variant of the function do mult() that must be called
   conditionally within a SIMD loop. The notinbranch clause on
   the declaration of the do pow() function tells the compiler
   that there is a SIMD variant of the function that must be
   called unconditionally within a SIMD loop.
*/
#pragma omp declare simd inbranch
float do_mult(float x)
{
  return (-2.0*x);
}

#pragma omp declare simd notinbranch
extern float do_pow(float);

void simd_loop_with_branch(float *a, float *b, int n)
{
  #pragma omp simd
  for (int i=0; i<n; i++) {
    if (a[i] < 0.0 )
      b[i] = do_mult(a[i]);

    b[i] = do_pow(b[i]);
  } /* --- end simd region --- */
}
