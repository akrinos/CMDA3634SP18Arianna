#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

int main(int argc, char **argv) {
	
	MPI_Init(&argc,&argv);
	int rank,size; 	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int N;

  //need running tallies
  long long int Ntotal = 0;
  long long int Ncircle = 0;

  //seed random number generator
  double seed = rank;
  srand48(seed);

  for (long long int n=0; n<100000;n++) {
    //gererate two random numbers
    double rand1 = drand48(); //drand48 returns a number between 0 and 1
    double rand2 = drand48();
    
    double x = -1 + 2*rand1; //shift to [-1,1]
    double y = -1 + 2*rand2;

    //check if its in the circle
    if (sqrt(x*x+y*y)<=1) Ncircle++;
    Ntotal++;
    if (n % 100 == 0) {
	double sum_recv = 0;
	//for (int i = 0; i < size; i++) {
		double curr;
		int tag = 1;
		MPI_Status status; 
		double juniorPI = (4.0 * Ncircle) / ((double) Ntotal);
		//printf("%f, at rank %d with ncircle %d\n", juniorPI, rank, (int)  Ncircle);
		MPI_Reduce(&juniorPI,&sum_recv,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	//}
	if (rank == 0) {
		//printf("%d size is\n", size);
		double average = sum_recv / size; 
		printf("The average estimate for pi after %d steps is %f\n", (int) n, average); 
	}
    }
  }

  double pi = 4.0*Ncircle/ (double) Ntotal;
/*
  //printf("Our estimate of pi is %f \n", pi);
	int sum_recv = 0;
	for (int i = 0; i < size; i++) {
		double curr;
		int tag = 1;
		MPI_Status status; 
		MPI_Send(&pi, 
			 1,
			 MPI_DOUBLE,
			 i,
			 tag,
			MPI_COMM_WORLD);
		if (rank == 0) {
			MPI_Recv(&curr, 
						1,
						MPI_DOUBLE,
						i,
						tag,
						MPI_COMM_WORLD,
						&status); 
			sum_recv += curr; 
		}	
	}
	if (rank == 0) {
		double average = sum_recv / size; 
		printf("The final average estimate for pi is %f\n", average); 
	}*/

	MPI_Finalize(); 
  return 0;
}
