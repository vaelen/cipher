#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cipher.h"

int main() {
  int i = 0;
  char *input  = "This, is a test!";
  char *key    = "to be or not to be, that is the question.";

  printf("  Input: %s\n", input);
  
  int length = strlen(input) + 1;
  
  char *encoded = malloc(length * sizeof(char));
  for (i = 0; i < length; i++) {
    encoded[i] = 0;
  }

  cipher(input, encoded, key, 0);
  printf("Encoded: %s\n", encoded);

  char *decoded = malloc(length * sizeof(char));
  for (i = 0; i < length; i++) {
    decoded[i] = 0;
  }
  
  cipher(encoded, decoded, key, 1);
  printf("Decoded: %s\n", input);

  free(encoded);
  free(decoded);

  return 0;
}
