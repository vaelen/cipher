#ifndef CIPHER_H
#define CIPHER_H

/*
  Copyright 2024 Andrew C. Young
  License: MIT
 */

/* 
 * Caesar Cipher w/ One Time Pad
 *
 * Both in and key should be c style strings (ending with \0)
 * out should be at least as long as in.
 * If encode is 0 then the method will decode, otherwise it will encode.
 * Returns the number of characters processed.
 */

int cipher(const char *in, char* out, const char* key, const int encode);

#endif
