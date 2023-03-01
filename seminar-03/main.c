#include <stdio.h>
#include <stdlib.h>

#include "array_utils.h"

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

int find_gcd_in_array(int array[ARRAY_LENGTH])
{
    int array_gcd = array[0];

    for (int i = 1; i < ARRAY_LENGTH; i++)
    {
        array_gcd = gcd(array_gcd, array[i]);
    }

    return array_gcd;
}

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

int main(void)
{
    int array[ARRAY_LENGTH];

    printf("Enter 10 numbers: ");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        scanf("%d", &array[i]);
    }

    printf("\nArray: [");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d", array[i]);
        if (i != ARRAY_LENGTH - 1) {
            printf(", ");
        }
    }

    int number_to_find = 0;
    int* pointer = NULL;

    printf("]\nSum: %d\n", find_sum_in_array(array));
    printf("Max: %d; Min: %d\n", find_min_in_array(array), find_max_in_array(array));
    printf("Number to find: ");
    scanf("%d", &number_to_find);
    pointer = find_number_in_array(array, number_to_find);
    if (pointer == NULL)
    {
        printf("Number not found in the array!");
    }
    else
    {
        printf("Address of the number: %p\n", (void*) pointer);
    }

    int gcd = find_gcd_in_array(array);

    printf("GCD: %d; Factors: [", gcd);
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("%d", array[i] / gcd);
        if (i != ARRAY_LENGTH - 1)
        {
            printf(", ");
        }
    }
    putchar(']');

    return EXIT_SUCCESS;
}
