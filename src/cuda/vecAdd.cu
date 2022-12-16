//
// Created by tony on 16/12/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
__global__ void vecAdd_core(float *a, float *b, float *c, int n,int intensity)
{
  // Get our global thread ID
  int id = blockIdx.x*blockDim.x+threadIdx.x;

  // Make sure we do not go out of bounds
  if (id < n)
  { float ru=0;
    float ta=0,tb=0;
    ta=a[id];
    tb=b[id];
    for(int k=0;k<intensity;k++)
    {
      ru+= ta+tb;
    }

    c[id] = ru;
  }

}
void vecAdd(float *h_a, float *h_b, float *h_c, int n, int intensity){
// Device input vectors
float *d_a;
float *d_b;
//Device output vector
float *d_c;
  // Size, in bytes, of each vector
  size_t bytes = n*sizeof(float);

  // Allocate memory for each vector on GPU
  cudaMalloc(&d_a, bytes);
  cudaMalloc(&d_b, bytes);
  cudaMalloc(&d_c, bytes);
  // Copy host vectors to device
  cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
  cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);

  int blockSize, gridSize;

  // Number of threads in each thread block
  blockSize = 32;

  // Number of thread blocks in grid
  gridSize = (int)ceil((float)n/blockSize);

  // Execute the kernel
  vecAdd_core<<<gridSize, blockSize>>>(d_a, d_b, d_c, n,intensity);

  // Copy array back to host
  cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
  // Release device memory
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
}