#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed;
  
  seed = clock(); //this will make your program run differently everytime
  //seed = 0; //uncomment this and you program will behave the same everytime it's run
  
  srand48(seed);


  //begin by getting user's input
	unsigned int n;

  printf("Enter a number of bits: ");
  scanf("%u",&n);

  //make sure the input makes sense
  if ((n<2)||(n>30)) {
  	printf("Unsupported bit size.\n");
		return 0;  	
  }

  int p;

  /* Q2.2: Use isProbablyPrime and randomXbitInt to find a random n-bit prime number */
	int curr = randXbitInt(n);
	while (!isProbablyPrime(curr)) {
		curr = randXbitInt(n);
	}
	p = curr; 

  printf("p = %u is probably prime.\n", p);

  /* Q3.2: Use isProbablyPrime and randomXbitInt to find a new random n-bit prime number 
     which satisfies p=2*q+1 where q is also prime */
  int q;
	printf("%d problem\n", (int) isProbablyPrime(15));
	curr = randXbitInt(n);
	while ((!isProbablyPrime(curr) || !isProbablyPrime(2 * curr + 1)) && (curr - 1) % 2 == 0) { 
//|| ((curr * 2) + 1) < pow(2, n-1) || ((curr * 2) + 1) > pow(2,n) ) {
		curr = randXbitInt(n);
		//printf("%d and %d and %d\n", curr, n, (2*curr + 1));
	}
	//q = curr;
	//p = 2*curr + 1;
	q = 2 * curr + 1;
	p = curr;

	printf("p = %u is probably prime and equals 2*q + 1. q= %u and is also probably prime.\n", p, q);  

	/* Q3.3: use the fact that p=2*q+1 to quickly find a generator */
	unsigned int g = findGenerator(p);

	printf("g = %u is a generator of Z_%u \n", g, p);  
	/* Bonus: continuation of ElGamal */
	int randomExp = rand() % ((g + 1 - 1) + 1); 
	//printf("we're here\n");
	unsigned int h = pow(g, randomExp); 
	printf("x is %d, g is %d, and h is %d. Shh, x is now a secret!\n", randomExp, g, h);
	// now we want to find x such that h = g^x; possible values of x are 1 through g
	bool found = false;
	double toCheck = g;
	//double toCheck = pow(g, i);
	for (int i = 1; i <= g; i++) {
		if (h == toCheck) {
			printf("We found the x, it's %d\n",i);
			found = true; 
			break; 
		}
		toCheck *= g;
	}	 
	if (!found) {
		printf("We weren't able to find the x.\n");
	}
  return 0;
}

/* quickly find a generator */
//unsigned int findGenerator(unsigned int p) {
	// 2 and q are the only factors of p-1 so we just check that 2 and q are not g^r == 1
//	int q = (p - 1) / 2;
//	for (unsigned int i = 1; i < p; i++) {
//		int res1 = (int) pow(i, 1) % p; 
//		int res2 = (int) pow(i, q) % p;
//		if (res1 != 1 && res2 != 1) {
//			return i;
//		}	
//	}
//	return 0;
//}
