/* Example of multiple declare simd directives for a function

   Multiple SIMD versions of the function are generated.
   The invocation of a specific version of the function is
   determined by where it is called.
*/
#pragma omp declare simd linear(pixel) uniform(mask) inbranch
#pragma omp declare simd linear(pixel) notinbranch
#pragma omp declare simd
extern void compute_pixel(char *pixel, char mask);
