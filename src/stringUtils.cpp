#include "Arduino.h"
#include "stringUtils.h"


// *************
// Allocate a new string, complete with
// trailing string termination character.
// *************
char* allocStr(int size) {
  size = size + 2;
  char* result = new char[size];
  for (int i = 0; i < size; i++ ) {
    *(result + i) = '\0';
  }
  return result;
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
      *(result + index + innerCounter) = *(args[counter] + innerCounter);
    }
    
    index += len;
  }
  return result;
}
