#include <stdio.h>
#include <stdlib.h>

#include "array_utils.h"

int main(void)
{
    int array[ARRAY_LENGTH];

    printf("Enter 10 numbers: ");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        scanf("%d", &array[i]);
    }

    printf("\nArray: ");
    print_array(ARRAY_LENGTH, array);

    int number_to_find = 0;
    int min = 0;
    int max = 0;
    find_max_min_in_array(ARRAY_LENGTH, array, &max, &min);

    printf("Sum: %d\n", find_sum_in_array(ARRAY_LENGTH, array));
    printf("Max: %d; Min: %d\n", max, min);
    printf("Number to find: ");
    scanf("%d", &number_to_find);

    int* pointer = NULL;
    pointer = find_number_in_array(array, number_to_find);
    if (pointer == NULL)
    {
        printf("Number not found in the array!");
    }
    else
    {
        printf("Address of the number: %p\n", (void*) pointer);
    }

    int gcd = find_gcd_in_array(ARRAY_LENGTH, array);
    int divided_array[ARRAY_LENGTH];

    copy_array(ARRAY_LENGTH, array, divided_array);
    divide_array(ARRAY_LENGTH, divided_array, gcd);

    printf("GCD: %d; Factors: ", gcd);

    print_array(ARRAY_LENGTH, divided_array);
    bubble_sort(ARRAY_LENGTH, array);
    printf("Sorted: ");
    print_array(ARRAY_LENGTH, array);

    return EXIT_SUCCESS;
}
