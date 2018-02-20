#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main() {

	int N;
	fprintf(stdout, "Enter an upper bound: ");
	scanf("%d", &N);
	fprintf(stdout, "\n");

	// make storage for flags
	int *isPrime = (int*) malloc(N*sizeof(int)); 

	// initialize, i.e. set everything 'true' 
	for (int n = 0; n < N; n++) {
		isPrime[n] = 1; 
	}

	int sqrtN = (int) sqrt(N); 

	for (int i = 2; i < sqrtN; i++) {
		if (isPrime[i]) { // if statements treat everything nonzero as true - if i is prime
			for (int j = i * i; j < N; j++) {
				isPrime[j] = 0; // set j not prime
			}					
		}
	} 

	// count the number of primes we found
	int cnt = 0;
	for (int n = 0; n < N; n++) {
		if (isPrime[n]) {
			cnt++;
		}	
	}

	// make a list of the primes
	int *primes = (int*) malloc(cnt * sizeof(int)); // needed cnt to know size to allocate

	cnt = 0;
	for (int n = 0; n < N; n++) {
		if (isPrime[n]) {
			primes[cnt] = n; // cnt++ means use current value of cnt then increment (++cnt increments first)
			cnt++; // could do in one line "primes[cnt++] = n" 
		}	
	}
	
	int ct = 1;
	// print out what we find
	for (int n = 0; n < N; n++) {
		if (isPrime[n]) {
			fprintf(stdout, "The %d -th prime is %d\n", ct, n);
			ct++;
		}
	}

}
