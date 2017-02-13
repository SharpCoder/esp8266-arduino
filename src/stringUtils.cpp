#include "Arduino.h"
#include "stringUtils.h"

#define ATOI_BUFFER_SIZE 128
const long STR_BUFFER_SIZE = 1024;

// This is necessary. Kinda.
// There are two types of buffers because I made
// poor choices early on and am still fixing it.
char* atoiBuffer;
char* strBuffer;
long strBufferIndex = 0;
long atoiBufferIndex = 0;

void initStringHelper() {
  strBuffer = k_allocStr(STR_BUFFER_SIZE);
  atoiBuffer = k_allocStr(ATOI_BUFFER_SIZE);
  char* tempBuffer = (char*)strBuffer;
  for(int i = 0; i < STR_BUFFER_SIZE; i++) {
    *((char*)tempBuffer + i) = '\0';
  }
}

void resetStringHelper() {
  strBufferIndex = 0;
  atoiBufferIndex = 0;

  for(int i = 0; i < STR_BUFFER_SIZE; i++) {
    *((char*)strBuffer + i) = '\0';
  }
}

char* cpystr(char* origin) {
  long len = strlen(origin);
  char* ptr = (char*)(allocStr(strlen(origin)));
  for(long i = 0; i < len; i++) {
    ptr[i] = *((char*)origin + i);
  }
  return ptr;
}

// *************
// Allocate a new string, complete with
// trailing string termination character.
// *************
char* allocStr(long sizeToAlloc) {
  int allocSize = sizeToAlloc + 2;
  
  if ((strBufferIndex + allocSize) > STR_BUFFER_SIZE) {
    Serial.println(strBufferIndex);
    Serial.println(allocSize);
    Serial.println("Critical memory fault.");
    strBufferIndex = 0;
  }

  char* result = ((char*)strBuffer + strBufferIndex);
  strBufferIndex += allocSize;
  for (int i = 0; i < allocSize; i++ ) {
    *((char*)result + i) = '\0';
  }
  return result;
}

// *************
// SYSTEM USE ONLY
// *************
char* k_allocStr(int size) {
  size = size + 2;
  char* result = malloc(sizeof(char) * size);
  for (int i = 0; i < size; i++ ) {
    *((char*)result + i) = '\0';
  }
  return &*result;
}


// *************
// Concatenate arbitrary amounts of strings.
// Useful when forming commands to send to the wifi module.
// *************
char* cat(char* args[], int size) {
  if (size <= 0) return NULL;
  int maxLength = 0, counter = 0, innerCounter = 0, index = 0, len = 0;
  for (counter = 0; counter < size; counter++) {
    maxLength += strlen(args[counter]);
  }
  
  char* result = allocStr(maxLength);
  for (counter = 0; counter < size; counter++) {
    len = strlen(args[counter]);
    for (innerCounter = 0; innerCounter < len; innerCounter++) {
      *((char*)result + index + innerCounter) = *(args[counter] + innerCounter);
    }
    
    index += len;
  }
  return result;
}

// This is not necessary.
char ctoi(byte num) {
  if (num > 9 || num < 0) return '0';
  return (char)(48 + num);
}


// Forgive me father for I have sined...
// Don't judge me. I learned the hard way that
// memory management on arduino is rubbish.
// This is also rubbish, but it works for an arbitrary amount
// of atoi calls without overflowing the poor arduino.
char* atoi(unsigned long number) {
  unsigned long temp = abs(number);
  unsigned long digits = 1;
  while(temp >= 10) {
    digits++;
    temp /= 10;
  }

  if (atoiBufferIndex + digits + 1 > ATOI_BUFFER_SIZE) {
    atoiBufferIndex = 0;
  }
  char* result = &*(atoiBuffer + atoiBufferIndex);
  atoiBufferIndex = (atoiBufferIndex + digits + 1) % ATOI_BUFFER_SIZE;

  for (int r = 0; r < digits + 1; r++) {
    *(result + r) = '\0';
  }
  
  for (int i = digits; i > 0; i--) {
    unsigned long top = 1;
    for ( int r = 1; r < i; r++) {
      top *= 10;
    }
    
    char val = ctoi(number / top);
    
    if ( number <= 0) {
      result[digits - i] = '0';
    } else {
      result[digits - i] = val;
      number -= (number / top) * top;
    }
  }
  
  return &*(char[digits + 1])result;
}
