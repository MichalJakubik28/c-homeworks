//
// Created by Wermington on 15.2.16.
//

#include "dynamic_lib.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"

#define UNUSED(a) ((void) (a))
#define NOT_IMPLEMENTED()                                      \
    do {                                                       \
        fprintf(stderr, "%s is not implemented!\n", __func__); \
        raise(SIGTERM);                                        \
    } while (0)

char *dyn_strcpy(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t length = strlen(str);
    char *ptr = malloc(length);

    if (ptr == NULL) {
        return NULL;
    }

    strcpy(ptr, str);
    return ptr;
}

char *dyn_strjoin(const char *pre, const char *post)
{
    if (pre == NULL || post == NULL) {
        return NULL;
    }

    size_t length = strlen(pre) + strlen(post);
    char *ptr = malloc(length);

    if (ptr == NULL) {
        return NULL;
    }

    strcpy(ptr, pre);
    strcpy(ptr + strlen(pre), post);
    return ptr;
}

char *read_line(void)
{
    size_t reserved = 1;
    size_t stored = 0;
    char *ptr = malloc(1);
    size_t free = 1;
    char curr_char = getchar();
    while (curr_char != EOF) {
        if (free == 0) {
            char *ptr2 = realloc(ptr, reserved << 1);
            if (ptr2 == NULL) {
                fprintf(stderr, "Failed to allocate memory");
                return NULL;
            }
            reserved = reserved << 1;
            ptr = ptr2;
        }
        if (curr_char == '\n') {
            break;
        }
        ptr[stored] = curr_char;
        free--;
        stored++;
        curr_char = getchar();
    }
    if (free == 0) {
        char *ptr2 = realloc(ptr, reserved + 1);
        if (ptr2 == NULL) {
            fprintf(stderr, "Failed to allocate memory");
            return NULL;
        }
        ptr = ptr2;
        stored++;
    }
    ptr[stored] = 0;

    return ptr;
}

void **dyn_alloc2d(size_t rows, const size_t row_sizes[rows])
{
    assert(rows > 0);
    assert(row_sizes != NULL);

    void **array = malloc(rows * sizeof(void*));

    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if (row_sizes[i] == 0) {
            array[i] = NULL;
            continue;
        }
        void *row = malloc(row_sizes[i]);

        // cannot allocate memory for column
        if (row == NULL) {
            dyn_free2d(array, rows);
            return NULL;
        }
        array[i] = row;
    }

    return array;
}

int dyn_free2d(void **memory, size_t rows)
{
    if (rows == 0 || memory == NULL) {
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        free(memory[i]);
    }
    free(memory);
    memory = NULL;
    return 0;
}

/**
 * BONUSES
 */

unsigned **pascal_triangle(size_t depth)
{
    assert(depth > 0);

    size_t sizes[depth];
    for (size_t i = 0; i < depth; i++) {
        sizes[i] = (i + 1) * sizeof(unsigned);
    }
    unsigned **pascal = (unsigned **) dyn_alloc2d(depth, sizes);
    if (pascal == NULL) {
        return NULL;
    }

    for (size_t row = 0; row < depth; row++) {
        for (size_t col = 0; col <= row; col++) {
            if (row == 0) {
                pascal[row][col] = 1;
                continue;
            }
            if (col == 0) {
                pascal[row][col] = pascal[row - 1][col];
                continue;
            }
            if (col == row) {
                pascal[row][col] = pascal[row - 1][col - 1];
                continue;
            }
            pascal[row][col] = pascal[row - 1][col - 1] + pascal[row - 1][col];
        }
    }

    return pascal;
}

char **string_split(const char *orig, const char *splitter, size_t *size)
{
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(orig);
    /* ! */ UNUSED(splitter);
    /* ! */ UNUSED(size);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
}

char *string_replace_all(const char *original, const char *from, const char *to)
{
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(original);
    /* ! */ UNUSED(from);
    /* ! */ UNUSED(to);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
}
