#include <string.h>
#include "cipher.h"

const char LCASE_START = 'a';
const char LCASE_END   = 'z';
const char UCASE_START = 'A';
const char UCASE_END   = 'Z';
const char UCASE_DIFF  = LCASE_START - UCASE_START;
const char UCASE_SIZE  = UCASE_END - UCASE_START;

int cipher(const char *in, char* out, const char* key, const int encode) {
  int i, j, t = 0;
  char c = in[i];
  char k = key[j];
  
  while (c != 0) {
    /* Upper case */
    if (c >= LCASE_START && c <= LCASE_END) {
      c -= UCASE_DIFF;
    }
    
    /* Only convert characters */
    if (c >= UCASE_START && c <= UCASE_END) {
      /* Check for next key value */
      while (k < UCASE_START || k > UCASE_END) {
	/* Invalid key */
	if (k >= LCASE_START && k <= LCASE_END) {
	  /* Convert to upper case */
	  k -= UCASE_DIFF;
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

      /* Convert character */
      if (encode != 0) {
	t = c + k;
      } else {
	t = c - k;
      }
      t = (t % UCASE_SIZE) + UCASE_START;
      c = (char)t;
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
