/* 

To compile:

   nvcc -O3 -o mandelbrot mandelbrot.c png_util.c -I. -lpng -lm -fopenmp

Or just type:

   module load gcc
   make

To create an image with 4096 x 4096 pixels (last argument will be used to set number of threads):

    ./mandelbrot 4096 4096 1

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "png_util.h"

// Q2a: add include for CUDA header file here:
#include "cuda.h"

#define MXITER 1000

typedef struct {
  
  double r;
  double i;
  
}complex_t;

// return iterations before z leaves mandelbrot set for given c
__device__ int testpoint(complex_t c){
  
  int iter;

  complex_t z;
  double temp;
  
  z = c;
  
  for(iter=0; iter<MXITER; iter++){
    
    temp = (z.r*z.r) - (z.i*z.i) + c.r;
    
    z.i = z.r*z.i*2. + c.i;
    z.r = temp;
    
    if((z.r*z.r+z.i*z.i)>4.0){
      return iter;
    }
  }
  
  
  return iter;
  
}

// perform Mandelbrot iteration on a grid of numbers in the complex plane
// record the  iteration counts in the count array

// Q2c: transform this function into a CUDA kernel
__global__ void  kernelMandelbrot(int Nre, int Nim, complex_t cmin, complex_t cmax, float *count){ 
  int tx = threadIdx.x;
  int ty = threadIdx.y;

  int bx = blockIdx.x;
  int by = blockIdx.y;

  int bSizex = blockDim.x;
  int bSizey = blockDim.y;

//  int n,m;

  complex_t c;

  double dr = (cmax.r-cmin.r)/(Nre-1);
  double di = (cmax.i-cmin.i)/(Nim-1);;

  int i = tx + bx * bSizex; // x coord
  int j = ty + by * bSizey; // y coord
  
  c.r = cmin.r + dr * i;
  c.i = cmin.i + di + j;
  //c.r = cmin.r + ty * i;
  //c.i = cmin.i + tx * j;
  count[i + j * Nre] = testpoint(c);
//  for(n=0;n<Nim;++n){
//   for(m=0;m<Nre;++m){
//      c.r = cmin.r + dr*m; // the m number is the real index 
//     c.i = cmin.i + di*n; // the n number is the imaginary index
      
//      count[m+n*Nre] = testpoint(c);
      
//    }
 // }

}

int main(int argc, char **argv){

  // to create a 4096x4096 pixel image [ last argument is placeholder for number of threads ] 
  // usage: ./mandelbrot 4096 4096 1  
  printf("here we go\n");  

  int Nre = atoi(argv[1]);
  int Nim = atoi(argv[2]);
  printf("Nre and Nim are %d and %d\n", Nre, Nim);
  int Nthreads = Nre * Nim; //atoi(argv[3]);
  int N = Nre * Nim;

  // Q2b: set the number of threads per block and the number of blocks here:
  float *fltArray;
  cudaMalloc(&fltArray, Nre*Nim*sizeof(float));

  int Nblocks = (int) (N + Nthreads - 1) / (Nthreads); 
  int Bx, By, Gx, Gy; 
  Bx = Nthreads;
  By = Nthreads;
  Gx = Nblocks;
  Gy = Nblocks;

  dim3 block(Bx, By, 1); // Bx * By threads in thread-block
  dim3 grid(Gx, Gy, 1); // Gx * Gy grid of thread-blocks 

  // storage for the iteration counts
  float *count = (float*) malloc(Nre*Nim*sizeof(float));

  // Parameters for a bounding box for "c" that generates an interesting image
  const float centRe = -.759856, centIm= .125547;
  const float diam  = 0.151579;

  complex_t cmin; 
  complex_t cmax;

  cmin.r = centRe - 0.5*diam;
  cmax.r = centRe + 0.5*diam;
  cmin.i = centIm - 0.5*diam;
  cmax.i = centIm + 0.5*diam;

  clock_t start = clock(); //start time in CPU cycles

  // compute mandelbrot set
  kernelMandelbrot<<<Nblocks , Nthreads >>>(Nre, Nim, cmin, cmax, count); 
  
  clock_t end = clock(); //start time in CPU cycles
  
  // print elapsed time
  printf("elapsed = %f\n", ((double)(end-start))/CLOCKS_PER_SEC);
  cudaMemcpy(fltArray, count, Nthreads * sizeof(float), cudaMemcpyDeviceToHost);

  // output mandelbrot to png format image
  //char Nre_str = malloc(sizeof(char)*(int)log10(Nre));
  //sprintf(&Nre_str, "%d", Nre);
  char randomLet = 'A' + (random() % 26);
  char* fileName = "mandelbrot"; 
  strcat(fileName, &randomLet);
  strcat(fileName, ".png");
  FILE *fp = fopen(fileName, "w");

  printf("Printing mandelbrot.png...");
  write_hot_png(fp, Nre, Nim, count, 0, 80);
  printf("done.\n");

  free(count);

  exit(0);
  return 0;
}  
