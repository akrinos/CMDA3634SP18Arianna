#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "functions.h"

// practice using things
//int main(int argc, char** argv) {
//	unsigned int num1 = 56;
//	unsigned int num2 = 74;
//	unsigned int num3 = 111;
//	printf("%d\n", modprod(num1, num2, num3));
//	printf("%d\n", modExp(num1, num2, num3)); 
//	printf("%d\n", isProbablyPrime(4));
//	printf("%d\n", isProbablyPrime(17));
//
//}

//compute a*b mod p safely
unsigned int modprod(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.2: Complete this function */
	int n = 0; 
	int bholder = b;
	while (bholder != 0) {
		bholder = bholder / 2;
		n++; 
	}
	// NOTE: this could be done easily by repeatedly dividing
	// b by two, but I originally implemented the b vector
	 
	bholder = b;
	int bvect[n];
	int t;
	int curr = pow(2, n-1);
	//printf("%d\n", curr);
	for (t = n-1; t >= 0; t--) {
		if (bholder / curr != 0) {
			bvect[t] = 1;
			bholder -= curr;
		} else {
			bvect[t] = 0; 
		}
		curr /= 2;
		//printf("the %d val is %d\n", t, bvect[t]); 
	}
	int za = a;
	int ab = 0;
	for (int i = 0; i < n; i++) {
		if (bvect[i] == 1) {
			ab = (ab + za*bvect[i]) % p; 
		}
		za = (2 * za) % p; 
	}
	return ab; 
}


//compute a^b mod p safely
unsigned int modExp(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.3: Complete this function */
	int z = a;
	int aExpb = 1;
	int n = 0;
	int bholder = b;
	while (bholder != 0) {
		bholder /= 2;
		n++;
	}
	bholder = b;	
	int bvect[n];
	int t;
	int curr = pow(2, n-1);
	//printf("%d\n", curr);

	// NOTE: this could be done easily by repeatedly dividing
	// b by two, but I originally implemented the b vector
	for (t = n-1; t >= 0; t--) {
		if (bholder / curr != 0) {
			bvect[t] = 1;
			bholder -= curr;
		} else {
			bvect[t] = 0; 
		}
		curr /= 2;
		//printf("the %d val is %d\n", t, bvect[t]); 
	}
	for (int i = 0; i < n; i++) {
		if (bvect[i] == 1) {
			aExpb = modprod(aExpb, z, p);
			//printf("%d\n", i);
		}
		z = modprod(z,z,p);
	}
	return aExpb;	
}

//returns either 0 or 1 randomly
unsigned int randomBit() {
  return rand()%2;
}

//returns a random integer which is between 2^{n-1} and 2^{n}
unsigned int randXbitInt(unsigned int n) {
  unsigned int r = 1;
  for (unsigned int i=0; i<n-1; i++) {
    r = r*2 + randomBit();
  }
  return r;
}

//tests for primality and return 1 if N is probably prime and 0 if N is composite
unsigned int isProbablyPrime(unsigned int N) {

  if (N%2==2) return 0; //not interested in even numbers (including 2)

  unsigned int NsmallPrimes = 168;
  unsigned int smallPrimeList[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
                                37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 
                                127, 131, 137, 139, 149, 151, 157, 163, 
                                167, 173, 179, 181, 191, 193, 197, 199, 
                                211, 223, 227, 229, 233, 239, 241, 251, 
                                257, 263, 269, 271, 277, 281, 283, 293, 
                                307, 311, 313, 317, 331, 337, 347, 349, 
                                353, 359, 367, 373, 379, 383, 389, 397, 
                                401, 409, 419, 421, 431, 433, 439, 443, 
                                449, 457, 461, 463, 467, 479, 487, 491, 
                                499, 503, 509, 521, 523, 541, 547, 557, 
                                563, 569, 571, 577, 587, 593, 599, 601, 
                                607, 613, 617, 619, 631, 641, 643, 647, 
                                653, 659, 661, 673, 677, 683, 691, 701, 
                                709, 719, 727, 733, 739, 743, 751, 757, 
                                761, 769, 773, 787, 797, 809, 811, 821, 
                                823, 827, 829, 839, 853, 857, 859, 863, 
                                877, 881, 883, 887, 907, 911, 919, 929, 
                                937, 941, 947, 953, 967, 971, 977, 983, 
                                991, 997};

  //before using a probablistic primality check, check directly using the small primes list
  for (unsigned int n=1;n<NsmallPrimes;n++) {
    if (N==smallPrimeList[n])   return 1; //true
    if (N%smallPrimeList[n]==0) return 0; //false
  }

  //if we're testing a large number switch to Miller-Rabin primality test
  /* Q2.1: Complete this part of the isProbablyPrime function using the Miller-Rabin pseudo-code */
  unsigned int r,d;
	int tempN = N - 1;
	r = 0;
	int divs = 1; 
	while (tempN > 0) {
		if ((N / divs) % 2 != 0) {	
			tempN = 0;
			d = (N / divs) % 2; 
		} else {
			divs *= 2; 
			r++;
		}  
	}
	

  for (unsigned int n=0;n<NsmallPrimes;n++) {
  	unsigned int a = randXbitInt(N);
	int x = modExp(a,d,N);
	if (x == 1 || x == N - 1) {
		continue;	
	}
	bool continueIt = false; 
	for (int i = 1; i < r - 1; i++) {
		x = modprod(x, x, N);
		if (x == 1) {
			return 0; //false
		} 
		if (x == N - 1) {
			continueIt = true; // continues to next k 
			break; 
		}
	}
	if (continueIt) {
		continue;
	}
	return 0; //false
  }
  return 1; //true
}

//Finds a generator of Z_p using the assumption that p=2*q+1
  /* Q3.3: complete this function and use the fact that p=2*q+1 to quickly find a generator *//* quickly find a generator */
unsigned int findGenerator(unsigned int p) {
        // 2 and q are the only factors of p-1 so we just check that 2 and q are not g^r == 1
        int q = (p - 1) / 2;
        for (unsigned int i = 1; i < p; i++) {
                int res1 = (int) pow(i, 1) % p;
                int res2 = (int) pow(i, q) % p;
                if (res1 != 1 && res2 != 1) {
                        return i;
                }
        }
        return 0;
}

