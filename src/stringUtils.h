#ifndef STRING_UTILS_H
#define STRING_UTILS_H

char* k_allocStr(int size);
char* allocStr(long size);
void initStringHelper();
void resetStringHelper();
char* cat(char*args[], int size);
char* atoi(unsigned long number);
char* cpystr(char* origin);
char ctoi(byte num);

#endif
