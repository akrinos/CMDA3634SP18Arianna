#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"
#include "functions.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  //seed value for the randomizer 
  double seed = clock()+rank; //this will make your program run differently everytime
  //double seed = rank; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  //begin with rank 0 getting user's input
  unsigned int n;

  /* Q3.1 Make rank 0 setup the ELGamal system and
    broadcast the public key information */ 

    //declare storage for an ElGamal cryptosytem
    unsigned int p, g, h, x;
  if (rank == 0) {
    //printf("Enter a number of bits: "); fflush(stdout);
    //char status = scanf("%u",&n);
    n = 10;
    //make sure the input makes sense
    if ((n<3)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
      printf("Unsupported bit size.\n");
      return 0;   
    }
    printf("\n");

    //declare storage for an ElGamal cryptosytem
    //unsigned int p, g, h, x;

    //setup an ElGamal cryptosystem
    p = randXbitInt(n);
    setupElGamal(n,&p,&g,&h,&x);
    int tag = 1;
  }
//    for (int i = 0; i < size; i++) {
      MPI_Bcast(&p, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
      MPI_Bcast(&g, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
      MPI_Bcast(&h, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
      MPI_Bcast(&x, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
 //   }
 // } else {
 //   MPI_Recv(&g, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 //   MPI_Recv(&p, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 //   MPI_Recv(&h, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 //   MPI_Recv(&x, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 //   printf("we're done receiving\n");
 //}


  //Suppose we don't know the secret key. Use all the ranks to try and find it in parallel
  if (rank==0)
    printf("Using %d processes to find the secret key...\n", size);

  /*Q3.2 We want to loop through values i=0 .. p-2
     determine start and end values so this loop is 
     distributed amounst the MPI ranks  */
  unsigned int N = p-1; //total loop size
  unsigned int start, end;
  int partition = N / size; 
  start = partition * rank; 
  end = start + partition; //start + N;
  // printf("we have start %d and end %d and x = %u and g = %u and p = %u, h = %u \n", start, end, x, g, p, h);
  if ((rank == size)) {
	end = N; // go to p-2 in the loop below 
  }

  MPI_Barrier(MPI_COMM_WORLD);
  double starttime; 
  if (rank == 0) {
	starttime = MPI_Wtime();
  }
  //loop through the values from 'start' to 'end'
  for (unsigned int i=start;i<end;i++) {
    if (modExp(g,i,p)==h)//+1,p)==h)
      printf("Secret key found! x = %u \n", i);
  }

  double endtime;
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
	printf("starting at %f\n", starttime);
	endtime = MPI_Wtime();
	printf("ending at %f\n", endtime);
  	double runtime = endtime - starttime;
 	double throughput = (N - 1) / runtime; // number of numbers we get through per second
 	printf("Our runtime is %f and throughput is %f. \n", runtime, throughput);
  }
  MPI_Finalize();

  return 0;
}
