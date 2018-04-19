#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);
void int_to_ascii(int n, char str[]);
int strlen(char str[]);
void reverse(char str[]);

#endif