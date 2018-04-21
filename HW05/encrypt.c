#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
  FILE * key;
  key = fopen("public_key.txt", "r");
  // message contains the string we want to convert to elements of Z_p
  char * currLine = NULL;
  size_t length = 0;
//  printf("now here1 \n");
  getline(&currLine, &length, key);
//  printf("now here2\n");
  n = atoi(currLine);
  currLine = NULL;
  getline(&currLine, &length, key);
  p = atoi(currLine);
  currLine = NULL;
  getline(&currLine, &length, key);
  g = atoi(currLine);
  currLine = NULL;
  getline(&currLine, &length, key);
  h = atoi(currLine);
  fclose(key);
//  printf("we're this far\n");

  padString(message, (n-1) / 8); 
  unsigned int *intsMess = malloc(((n-1) / 8) * sizeof(unsigned int));
  convertStringToZ(message, strlen(message), intsMess, (strlen(message))/ ((n-1)/8)); // last argument is strlen div chars per int = num ints
  
  unsigned int * a = malloc(strlen(message) * sizeof(unsigned int));
  ElGamalEncrypt(intsMess, a, strlen(message) / ((n-1)/8), p, g, h);

  FILE * mess;
  mess = fopen("message.txt","w");
  int i = 0;
  fprintf(mess, "%d\n", (int) strlen(message) / ((n-1)/8));
  for (i = 0; i < (strlen(message) / ((n-1)/8)); i++) {
	fprintf(mess, "%d %d\n", intsMess[i], a[i]);
  }
  fclose(mess);
	
  return 0;
}
