
mandelbrot : mandelbrot.o png_util.o 
	nvcc -arch=sm_60 -o mandelbrot cudaMandelbrot.o png_util.o -lpng -lm

mandelbrot.o : mandelbrot.cu png_util.h
	nvcc -arch=sm_60 -I. -c cudaMandelbrot.cu

png_util.o : png_util.c png_util.h
	nvcc -arch=sm_60 -I. -c png_util.c

clean :
	rm cudaMandelbrot.o png_util.o mandelbrot
