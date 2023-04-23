#include "big_int.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void subtract_unsigned(const big_int *a, const big_int *b, big_int *dest)
{
    int borrow = 0;
    for (int i = BIG_INT_DIGITS - 1; i >= 0; i--) {
        int diff = a->digits[i] - b->digits[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        dest->digits[i] = diff;
    }
}

void add_unsigned(const big_int *a, const big_int *b, big_int *dest)
{
    int carry = 0;
    for (int i = BIG_INT_DIGITS - 1; i >= 0; i--) {
        int sum = a->digits[i] + b->digits[i] + carry;
        dest->digits[i] = sum % 10;
        carry = sum / 10;
    }
}

void big_int_init(big_int *n)
{
    memset(n->digits, 0, sizeof(n->digits));
    n->is_positive = true;
}

void big_int_convert(big_int *dest, const long to_convert)
{
    char str_convert[19];
    memset(str_convert, 0, 19);
    snprintf(str_convert, 19, "%18ld", to_convert < 0 ? -to_convert : to_convert);
    dest->is_positive = to_convert >= 0;
    for (int i = 0; i < 18; i++) {
        if (str_convert[i] == ' ') {
            dest->digits[i + 3] = 0;
            continue;
        }
        dest->digits[i + 3] = str_convert[i] - 48;
    }
}

void delete_decimals(big_int *n)
{
    for (int i = 17; i < BIG_INT_DIGITS; i++) {
        n->digits[i] = 0;
    }
}

void big_int_round(big_int *n)
{
    if (n->digits[17] >= 5) {
        for (int i = 16; i >= 0; i--) {
            n->digits[i] = (n->digits[i] + 1);
            if (n->digits[i] == 10) {
                n->digits[i] = 0;
            } else {
                delete_decimals(n);
                return;
            }
        }
    }
    delete_decimals(n);
}

void big_int_print(big_int *n)
{
    if (!n->is_positive) {
        putchar('-');
    }
    int index = 0;
    while (n->digits[index] == 0 && index < 14) {
        index++;
    }
    while (index != 17) {
        if (index == 15) {
            if (n->digits[15] == 0 && n->digits[16] == 0) {
                return;
            }
            putchar('.');
            putchar(n->digits[index] + 48);
        } else {
            putchar(n->digits[index] + 48);
        }
        index++;
    }
}

void big_int_div_by_int(const big_int *n, big_int *dest, int divisor)
{
    dest->is_positive = n->is_positive;
    if (divisor < 0) {
        dest->is_positive = !n->is_positive;
        divisor = -divisor;
    }
    int rem = 0;
    for (int i = 0; i < BIG_INT_DIGITS; i++) {
        int div = (rem * 10 + n->digits[i]) / divisor;
        rem = (rem * 10 + n->digits[i]) % divisor;
        dest->digits[i] = div;
    }
}

int compare_unsigned(const big_int *a, const big_int *b)
{
    for (int i = 0; i < BIG_INT_DIGITS; i++) {
        if (a->digits[i] > b->digits[i]) {
            return 1;
        }
        if (a->digits[i] < b->digits[i]) {
            return -1;
        }
    }
    return 0;
}

int big_int_cmp(const big_int *a, const big_int *b, int sign)
{
    if (a->is_positive != b->is_positive) {
        return a->is_positive ? 1 : -1;
    }

    return compare_unsigned(a, b) * sign;
}

void big_int_subtract(big_int *a, big_int *b, big_int *dest)
{
    // switch if a is smaller than b
    if (a->is_positive != b->is_positive) {
        add_unsigned(a, b, dest); // ignore sign
        dest->is_positive = a->is_positive;
    } else if ((a->is_positive && big_int_cmp(a, b, 1) >= 0) || (!a->is_positive && big_int_cmp(a, b, 1) < 0)) {
        subtract_unsigned(a, b, dest);
        dest->is_positive = true;
    } else if (a->is_positive && big_int_cmp(a, b, 1) < 0) {
        subtract_unsigned(b, a, dest);
        dest->is_positive = false;
    } else if (!a->is_positive && big_int_cmp(a, b, 1) >= 0) {
        subtract_unsigned(a, b, dest);
        dest->is_positive = false;
    } else {
        assert(false);
    }
}

void big_int_add(big_int *a, big_int *b, big_int *dest)
{
    if (a->is_positive == b->is_positive) {
        add_unsigned(a, b, dest);
        dest->is_positive = a->is_positive;
    } else if (!a->is_positive && compare_unsigned(a, b) <= 0) {
        subtract_unsigned(b, a, dest);
        dest->is_positive = true;
    } else if (!a->is_positive && compare_unsigned(a, b) > 0) {
        subtract_unsigned(a, b, dest);
        dest->is_positive = false;
    } else if (a->is_positive && compare_unsigned(a, b) < 0) {
        subtract_unsigned(b, a, dest);
        dest->is_positive = false;
    } else if (a->is_positive && compare_unsigned(a, b) >= 0) {
        subtract_unsigned(a, b, dest);
        dest->is_positive = true;
    } else {
        assert(false);
    }
}

bool big_int_is_zero(const big_int *n, int tolerance)
{
    for (int i = 0; i < BIG_INT_DIGITS - tolerance; i++) { // not checking last <tolerance> digits
        if (n->digits[i] != 0) {
            return false;
        }
    }
    return true;
}
