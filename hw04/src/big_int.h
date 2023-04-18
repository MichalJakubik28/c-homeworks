#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdbool.h>

#define BIG_INT_DIGITS 25

typedef struct {
    int digits[BIG_INT_DIGITS];
    bool is_positive;
} big_int;

void big_int_init(big_int *n);
void big_int_convert(big_int *n, long to_convert);
void big_int_add(big_int *a, big_int *b, big_int *dest);
void big_int_print(big_int *n);
void big_int_div_by_int(const big_int *n, big_int *dest, int d);
int big_int_cmp(const big_int *a, const big_int *b, int sign);
void big_int_subtract(big_int *a, big_int *b, big_int *dest);
bool big_int_is_zero(const big_int *n, int tolerance);
double big_int_to_double(big_int *n);


#endif //BIG_INT_H
