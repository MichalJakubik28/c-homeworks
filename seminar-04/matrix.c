#include <stdio.h>
#include <stdlib.h>

void fill_matrix(int min_value, int max_value, size_t mrows, size_t mcols, int matrix[mrows][mcols]);
void print_matrix(size_t mrows, size_t mcols, int matrix[mrows][mcols]);

int main(void)
{
    printf("Work on matrices\n");
    return 0;
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
