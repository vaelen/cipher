/*
  Copyright 2024 Andrew C. Young
  License: MIT
 */
#include <string.h>
#include "cipher.h"

int cipher(const char *in, char* out, const char* key, const int encode) {
  int i, j = 0;
  char c = in[i];
  char k = key[j];
  char t = 0;
  
  while (c != 0) {
    /* Upper case */
    if (c >= 'a' && c <= 'z') {
      c -= 32;
    }
    
    /* Only convert characters */
    if (c >= 'A' && c <= 'Z') {
      /* Check for next key value */
      while (k < 'A' || k > 'Z') {
	/* Invalid key */
	if (k >= 'a' && k <= 'z') {
	  /* Convert to upper case */
	  k -= 32;
	} else {
	  if (k == 0) {
	    /* End of key, wrap */
	    j = 0;
	  } else {
	    j++;
	  }
	  k = key[j];
	}
      }

      k -= 'A';
      
      /* Convert character */
      if (encode) {
	t = c + k;
      } else {
	t = c - k;
      }
      if (t > 'Z') {
	t -= 26;
      } else if (t < 'A') {
	t += 26;
      }
      c = t;
    }

    /* Output character */
    out[i] = c;

    /* Increment input and key */
    i++;
    j++;
    c = in[i];
    k = key[j];
  }
  return i;
}
