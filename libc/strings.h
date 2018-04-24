#pragma once
#include <stdbool.h>
#include <stdint.h>

void hex_to_ascii(int n, char str[]);
void int_to_ascii(int n, char str[]);
int strlen(char str[]);
int strcompare(uint8_t str1[], uint8_t str2[]);
void reverse(char str[]);
void append(char str[], char n);