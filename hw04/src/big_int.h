#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdbool.h>

#define BIG_INT_DIGITS 25

/** @brief Structure representing a big integer **/
typedef struct
{
    int digits[BIG_INT_DIGITS];
    bool is_positive;
} big_int;

/**
 * @brief Rounds big_int number to 2 decimal numbers.
 * Considers number being 15 digits long before decimal
 * dot and the rest after.
 *
 * @param n big_int number
 */
void big_int_round(big_int *n);

/**
 * @brief Initializes big_int as 0 (defined as positive number).
 *
 * @param n big_int number
 */
void big_int_init(big_int *n);

/**
 * @brief Converts long variable to big_int
 *
 * @param dest target big_int number
 * @param to_convert long integer to convert
 *
 */
void big_int_convert(big_int *dest, long to_convert);

/**
 * @brief Adds together 2 big_int numbers and saves the
 * result into the target big_int number.
 *
 * @param a big_int number
 * @param b big_int number
 * @param dest big_int where the result of a + b will be saved to
 */
void big_int_add(big_int *a, big_int *b, big_int *dest);

/**
 * @brief Prints big_int number as a number with 15 digits before decimal dot.
 * Also prints first two decimal digits of the number.
 *
 * @param n big_int number
 */
void big_int_print(big_int *n);

/**
 * @brief Divides big_int by an integer and saves
 * it to the target big_int number.
 *
 * @param n big_int number
 * @param dest destination big_int number
 * @param d divisor
 */
void big_int_div_by_int(const big_int *n, big_int *dest, int d);

/**
 * @brief Compares 2 big_int numbers.
 *
 * @param a big_int number
 * @param b big_int number
 * @param sign number indicating whether a smaller
 * or bigger number is to be returned.
 *
 * @retval sign * positive integer if a > b, sign * negative if b > a, 0 if a = b.
 */
int big_int_cmp(const big_int *a, const big_int *b, int sign);

/**
 * @brief Subtracts the second number from the first one and saves the
 * result into the target big_int number.
 *
 * @param a first big_int number
 * @param b second big_int number
 * @param dest big_int where the result of a - b will be saved to
 */
void big_int_subtract(big_int *a, big_int *b, big_int *dest);

/**
 * @brief Checks whether a big_int number is equal to 0,
 * ignoring the last <tolerance> digits
 *
 * @param n big_int number
 * @param tolerance number of least significant digits to be ignored
 * @retval true if n is equal to zero when the last <tolerance> digits are ignored.
 */
bool big_int_is_zero(const big_int *n, int tolerance);

#endif //BIG_INT_H
