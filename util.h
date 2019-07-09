#ifndef __UTIL_H
#define __UTIL_H
#include <stdio.h>

int to_int(const char *number);

char *get_1K0();

char *get_1K1();

void set_bits(FILE *fp, int offset, int number, char tag);

#endif //  __UTIL_H