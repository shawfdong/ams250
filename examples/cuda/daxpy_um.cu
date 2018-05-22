#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 20480

// declare the kernel
__global__ void daxpy(double a, double *x, double *y) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        y[i] += a*x[i];
    }
}

int main(void) {
    double *x, *y, a;
    double m = -1.;
    double tmp;
    int i;
    size_t size = N*sizeof(double);

    // allocate unified memory
    cudaMallocManaged(&x, size);
    cudaMallocManaged(&y, size);

    // initialize x and y
    srand(time(NULL));
    a = (double)random() / RAND_MAX;
    for (i=0; i<N; i++)
        x[i] = (double)random() / RAND_MAX;
    for (i=0; i<N; i++)
        y[i] = (double)random() / RAND_MAX;

    // launch the kernel function
    daxpy<<<N/256,256>>>(a, x, y);

    cudaDeviceSynchronize();

    // deallocate device memory
    cudaFree(x);
    cudaFree(y);
}
