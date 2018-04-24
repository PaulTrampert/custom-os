#include <stdint.h>
#include <stdbool.h>
#include "strings.h"

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') ++i;
    return i;
}

void reverse(char str[]) {
    int c, i, j;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void append(char str[], char n) {
  int len = strlen(str);
  str[len] = n;
  str[len+1] = '\0';
}

int strcompare(uint8_t str1[], uint8_t str2[]) {
    int i;
    int strlen1 = strlen(str1);
    int strlen2 = strlen(str2);
    for (i = 0; i < strlen1 && i < strlen2; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        if (str1[i] > str2[i]) {
            return 1;
        }
    }
    if (strlen1 < strlen2) {
        return -1;
    }
    if (strlen1 > strlen2) {
        return 1;
    }
    return 0;
}