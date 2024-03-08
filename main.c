/*
  Copyright 2024 Andrew C. Young
  License: MIT
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cipher.h"

void header() {
  fprintf(stderr, "Caeser Cipher Encoder/Decoder\n");
  fprintf(stderr, "(C)2024 Andrew C. Young\n");
  fprintf(stderr, "Email: andrew@vaelen.org>, fsxNet: vaelen@21:1/141\n");
}

void usage() {
  fprintf(stderr, "usage: cipher <e|d> <keyfile> [inputfile]\n");
}  

int readKey(FILE *keyFile, char *key, int size) {
  int i = 0;
  while (i < size && !feof(keyFile) && !ferror(keyFile)) {
    char c = getc(keyFile);
    if (c >= 'a' && c <= 'z') {
      c -= 32;
    }
    if (c >= 'A' && c <= 'Z') {
      key[i++] = c;
    }
  }
  return i;
}

int main(int argc, char *argv[]) {
  int i, encode = 0;

  header();
  
  if (argc < 3) {
    usage();
    return 1;
  }

  char *mode = argv[1];
  char *keyFilename = argv[2];
  char *inputFilename = NULL;
  char *outputFilename = NULL;

  if (argc >= 4) {
    inputFilename = argv[3];
  }

  if (argc >= 5) {
    outputFilename = argv[4];
  }

  switch (mode[0]) {
  case 'e':
    encode = 1;
    break;
  case 'd':
    encode = 0;
    break;
  default:
    usage();
    return 1;
  }

  char input[4096], output[4096], key[4096];

  for (i = 0; i < 4096; i++) {
    input[i] = 0;
    output[i] = 0;
    key[i] = 0;
  }

  FILE *keyFile = fopen(keyFilename, "r");
  if (keyFile == NULL) {
    fprintf(stderr, "Couldn't open file: %s\n", keyFilename);
    return 1;
  }

  i = readKey(keyFile, key, 4095);
  if (i == 0) {
    fprintf(stderr, "Key file is empty: %s\n", keyFilename);
    return 1;
  }
  key[i] = 0;

  fclose(keyFile);

  fprintf(stderr,
	  "     Mode: %s\n      Key: %s\n    Input: %s\n    Output: %s\n\n",
	  encode == 0 ? "Decode" : "Encode",
	  keyFilename,
	  inputFilename != NULL ? inputFilename : "<stdin>", 
	  outputFilename != NULL ? outputFilename : "<stdout>"); 
  
  FILE *inFile = stdin;
  if (inputFilename != NULL) {
    inFile = fopen(inputFilename, "r");
    if (inFile == NULL) {
      fprintf(stderr, "Couldn't open file: %s\n", inputFilename);
      return 1;
    }
  }

  FILE *outFile = stdout;
  if (outputFilename != NULL) {
    outFile = fopen(outputFilename, "w");
    if (outFile == NULL) {
      fprintf(stderr, "Couldn't open file: %s\n", inputFilename);
      return 1;
    }
  }
  
  while (!feof(inFile) && !ferror(inFile)) {
    i = fread(input, 1, 4095, inFile);
    input[i] = 0;
    cipher(input, output, key, encode);
    fputs(output, outFile);
  }

  fclose(inFile);
  fclose(outFile);
  
  return 0;
}
