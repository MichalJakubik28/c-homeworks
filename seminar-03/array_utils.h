#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stddef.h>

#define ARRAY_LENGTH 15

int *find_number_in_array(int array[ARRAY_LENGTH], int number);

int find_sum_in_array(size_t length, const int *array);

int find_gcd_in_array(size_t length, const int *array);

int find_max_min_in_array(size_t length, const int *array, int *max, int *min);

void print_array(size_t length, const int *array);

void copy_array(size_t length, const int *orig_array, int *new_array);

void divide_array(size_t length, int *array, int divisor);

void swap(int *x, int *y);

void bubble_sort(size_t length, int *array);

#endif
