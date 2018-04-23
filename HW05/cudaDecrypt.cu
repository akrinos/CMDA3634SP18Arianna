#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"


int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
  FILE * key; 
  key = fopen("public_key.txt", "r");
  char * currLine = NULL; size_t length = 0;
  getline(&currLine, &length, key);
  n = atoi(currLine); currLine = NULL;
  getline(&currLine, &length, key);
  p = atoi(currLine); currLine = NULL;
  getline(&currLine, &length, key);
  g = atoi(currLine), currLine = NULL;
  getline(&currLine, &length, key);
  h = atoi(currLine); fclose(key); 

  FILE * messge;
  messge = fopen("message.txt", "r");
  currLine = NULL; length = 0;
  getline(&currLine, &length, key);
  int numEnt = atoi(currLine); currLine = NULL;
  unsigned int * m = malloc(numEnt * sizeof(unsigned int));
  unsigned int * a = malloc(numEnt * sizeof(unsigned int));
  for (int i = 0; i < numEnt; i++) {
	getline(&currLine, &length, key);
	m[i] = atoi(strtok(currLine, " "));
	a[i] = atoi(strtok(NULL, " ")); 
//	printf("we've got %d and %d\n", m[i],a[i]);
	currLine = NULL; 
  } 

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  // Feed in [m] and [a] to the decrypt function 
  Nints = numEnt;
  unsigned int Nchars = numEnt * ((n - 1) / 8);
  ElGamalDecrypt(m, a, Nints, p, x);
  char * final = malloc(Nchars * sizeof(char));
  convertZToString(m, Nints, final, Nchars);
  // printf("%s\n", final); 
  return 0;
  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

  return 0;
}
