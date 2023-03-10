#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 5
#define BOARD_SIZE 3

void fill_matrix(int min_value, int max_value, size_t mrows, size_t mcols, int matrix[mrows][mcols]);
void print_matrix(size_t mrows, size_t mcols, int matrix[mrows][mcols]);
void multiply_matrix(size_t mrows, size_t mcols, int matrix[mrows][mcols], int number);
int find_max_min_in_array(size_t length, const int *array, int *max, int *min);
int find_max_min_pointers(size_t length, int *array, int **max, int **min);
int find_palindromes(size_t mrows, size_t mcols, int matrix[mrows][mcols], bool palindromes[mrows]);

int main(void)
{
    // Task 1
    printf("TASK 1:\n");

    int matrix[ARRAY_SIZE][ARRAY_SIZE];
    printf("matrix is pointing to %p with size of %zu\n", (void*) matrix, sizeof(matrix));
    printf("matrix[0] is pointing to %p with size of %zu\n", (void*) matrix[0], sizeof(matrix[0]));
    printf("matrix[1] is pointing to %p with size of %zu\n", (void*) matrix[1], sizeof(matrix[1]));
    printf("matrix[1][1] is pointing to %p with size of %zu\n", (void*) &matrix[1][1], sizeof(matrix[1][1]));

    printf("\n\n");


    // Task 2
    printf("TASK 2:\n");

    fill_matrix(0, 10, ARRAY_SIZE, ARRAY_SIZE, matrix);
    printf("Matrix before multiplying:\n");
    print_matrix(ARRAY_SIZE, ARRAY_SIZE, matrix);
    putchar('\n');
    multiply_matrix(ARRAY_SIZE, ARRAY_SIZE, matrix, 10);
    printf("Matrix after multiplying:\n");
    print_matrix(ARRAY_SIZE, ARRAY_SIZE, matrix);

    printf("\n\n");


    // Task 3
    printf("TASK 3:\n");

    int min = 0;
    int max = 0;

    find_max_min_in_array(sizeof(matrix) / sizeof(int), (int*) matrix, &max, &min);
    printf("Max: %d, Min: %d\n", max, min);
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        find_max_min_in_array(sizeof(matrix[i]) / sizeof(int), matrix[i], &max, &min);
        printf("Row no. %d, max: %d, min: %d\n", i, max, min);
    }

    printf("\n\n");


    // Task 4
    printf("TASK 4:\n");

    int *maximum = 0;
    int *minimum = 0;

    find_max_min_pointers(sizeof(matrix) / sizeof(int), (int*) matrix, &maximum, &minimum);
    printf("Found max in matrix %d on coordinates [%ld][%ld]\n", *maximum, (maximum - matrix[0]) / ARRAY_SIZE, (maximum - matrix[0]) % ARRAY_SIZE);
    printf("Found min in matrix %d on coordinates [%ld][%ld]\n", *minimum, (minimum - matrix[0]) / ARRAY_SIZE, (minimum - matrix[0]) % ARRAY_SIZE);

    printf("\n\n");


    // Task 5
    printf("TASK 5:\n");

    int test_palindromes[5][5] = {{1,2,3,2,1},  // palindrome
                     {23, 34, 45, 34, 23},      // palindrome
                     {1, 2, 3, 4, 5},           // not palindrome
                     {0, 1, 0, 0, 0},           // not palindrome
                     {0, 0, 1, 0, 0}};          // palindrome

    bool palindromes[ARRAY_SIZE];
    int no_of_palindromes = find_palindromes(ARRAY_SIZE, ARRAY_SIZE,test_palindromes, palindromes);

    printf("No. of palindromes in array: %d\n", no_of_palindromes);
    printf("Palindromes on lines");

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (palindromes[i] == true)
        {
            printf(" %d", i);
        }
    }
    putchar('\n');

    return 0;
}

int find_palindromes(size_t mrows, size_t mcols, int matrix[mrows][mcols], bool palindromes[mrows])
{
    int palindrome_count = 0;
    for (size_t i = 0; i < mrows; i++)
    {
        int *first = matrix[i];
        int *last = matrix[i + 1] - 1;
        while (first < last)
        {
            if (*first != *last)
            {
                break;
            }
            first += 1;
            last -= 1;
        }
        palindromes[i] = false;
        if (first >= last)
        {
            palindrome_count += 1;
            palindromes[i] = true;
        }
    }
    return palindrome_count;
}

int find_max_min_pointers(size_t length, int *array, int **max, int **min)
{
    if (array == NULL)
    {
        return 0;
    }

    if (max == NULL && min == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (max != NULL && (i == 0 || array[i] > **max))
        {
            *max = &array[i];
        }

        if (min != NULL && (i == 0 || array[i] < **min))
        {
            *min = &array[i];
        }
    }

    if (max != NULL && min != NULL)
    {
        return 2;
    }

    return 1;
}

int find_max_min_in_array(size_t length, const int *array, int *max, int *min)
{
    if (array == NULL)
    {
        return 0;
    }
    
    if (max == NULL && min == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (max != NULL && (i == 0 || array[i] > *max))
        {
            *max = *(array + i);
        }

        if (min != NULL && (i == 0 || array[i] < *min))
        {
            *min = array[i];
        }
    }

    if (max != NULL && min != NULL)
    {
        return 2;
    }

    return 1;
}

void multiply_matrix(size_t mrows, size_t mcols, int matrix[mrows][mcols], int number)
{
    for (size_t i = 0; i < mrows; i++)
    {
        for (size_t j = 0; j < mcols; j++)
        {
            matrix[i][j] *= number;
        }
    }
}

void fill_matrix(int min_value, int max_value, size_t mrows, size_t mcols, int matrix[mrows][mcols])
{
    if (max_value <= min_value) {
        return;
    }

    for (size_t i = 0; i < mrows; i++) {
        for (size_t j = 0; j < mcols; j++) {
            matrix[i][j] = rand() % (max_value - min_value) + min_value;
        }
    }
}

void print_matrix(size_t mrows, size_t mcols, int matrix[mrows][mcols])
{
    for (size_t i = 0; i < mrows; i++) {
        for (size_t j = 0; j < mcols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
