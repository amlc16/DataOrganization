#include <stdio.h>
#include <string.h>

/* Alexander Leon*/
  int main( int argc, char *argv[] ) {

  if ( argc != 2 ) {
    printf ( "You must enter a single argument on the command line\n" );
    return 1;  // Error code for operating system
  }

  char *theData = argv[1];

  unsigned int hashCode = 0;
  unsigned int shiftedOut;
  int i;
  for ( i = 0; i < strlen(theData); i++ ) {
    char currentChar = theData[i];
    hashCode = hashCode + (unsigned int)currentChar;
    if (i <strlen(theData)-1){
        shiftedOut = hashCode >> 28;
        hashCode = hashCode << 4;
        hashCode = hashCode ^ (shiftedOut << 18);
    }
  }
  printf("The hash of %s = %u\n", theData, hashCode);
  return 0;
}
