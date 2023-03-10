#include "array_utils.h"
#include <stdio.h>

int *find_number_in_array(int array[ARRAY_LENGTH], int number)
{
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        if (array[i] == number)
        {
            return &array[i];
        }
    }

    return NULL;
}

int find_sum_in_array(size_t length, const int *array)
{
    if (array == NULL)
    {
        return 0;
    }

    int sum = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        sum += *(array + i);
    }
    return sum;
}

int find_max_min_in_array(size_t length, const int *array, int *max, int *min)
{
    if (max == NULL && min == NULL)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (max != NULL && (i == 0 || *(array + i) > *max))
        {
            *max = *(array + i);
        }

        if (min != NULL && (i == 0 || *(array + i) < *min))
        {
            *min = *(array + i);
        }
    }

    if (max != NULL && min != NULL)
    {
        return 2;
    }

    return 1;
}

int gcd(int a, int b)
{
    if (a < b)
    {
        return gcd(b, a);
    }

    while (b != 0)
    {
        int r = a;
        a = b;
        b = r % b;
    }

    return a;
}

int find_gcd_in_array(size_t length, const int *array)
{
    if (array == NULL)
    {
        return 0;
    }

    int array_gcd = *array;

    for (int i = 1; i < length; i++)
    {
        array_gcd = gcd(array_gcd, *(array + i));
    }

    return array_gcd;
}

void print_array(size_t length, const int *array)
{
    putchar('[');
    for (unsigned int i = 0; i < length; i++)
    {
        printf("%d", *(array + i));
        if (i != length - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void copy_array(size_t length, const int *orig_array, int *new_array)
{
    for (unsigned int i = 0; i < length; i++)
    {
        *(new_array + i) = *(orig_array + i);
    }
}

void divide_array(size_t length, int *array, int divisor)
{
    for (unsigned int i = 0; i < length; i++)
    {
        *(array + i) = *(array + i) / divisor;
    }
}

void swap(int *x, int *y)
{
    int aux = *y;
    *y = *x;
    *x = aux;
}

void bubble_sort(size_t length, int *array)
{
    for (int i = length - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (*(array + j) > *(array + j + 1))
            {
                swap(array + j, array + j + 1);
            }
        }
    }
}
