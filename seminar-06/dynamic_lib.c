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


size_t count_splitters(const char *string, const char *splitter)
{
    if (string == NULL || splitter == NULL) {
        return 0;
    }
    const char *start = string;
    int counter = 0;
    while (start < string + strlen(string)) {
        if (strncmp(start, splitter, strlen(splitter)) == 0) {
            counter++;
            start += strlen(splitter) - 1;
        }
        start++;
    }

    return counter;
}


char **string_split(const char *orig, const char *splitter, size_t *size)
{
    assert(orig != NULL);
    assert(splitter != NULL);
    assert(size != NULL);

    size_t result_size = count_splitters(orig, splitter);

    char **result = malloc((result_size + 2) * sizeof(void*));
    if (result == NULL) {
        return NULL;
    }

    // I know the size of the array in <size> and it is not a string so why must the last pointer in array be null?
    result[result_size + 1] = NULL;

    int counter = 0;
    const char *start = orig;
    char *nearest_delim = strstr(start, splitter);

    if (orig[0] == 0) {
        *size = 0;
        return NULL;
    }

    char *substring;

    while (nearest_delim != NULL) {
        long diff = nearest_delim - start;
        substring = malloc(diff + 1);

        // cannot allocate memory for substring
        if (substring == NULL) {
            for (int i = 0; i < counter; i++) {
                free(result[i]);
                result[i] = NULL;
            }
            result = NULL;
            return NULL;
        }

        strncpy(substring, start, diff);
        substring[diff] = 0;
        result[counter] = substring;
        counter += 1;
        start = nearest_delim + strlen(splitter);
        nearest_delim = strchr(start, *splitter);
    }

    size_t length_of_last = orig + strlen(orig) - start;
    substring = malloc(length_of_last + 1);

    // cannot allocate memory for last substring
    if (substring == NULL) {
        for (int i = 0; i < counter; i++) {
            free(result[i]);
            result[i] = NULL;
        }
        result = NULL;
        return NULL;
    }

    strncpy(substring, start, length_of_last);
    substring[length_of_last] = 0;
    result[counter] = substring;
    *size = counter + 1;
    return result;
}

char *string_replace_all(const char *original, const char *from, const char *to)
{
    assert(original != NULL);
    assert(from != NULL);
    assert(to != NULL);

    size_t substring_count = count_splitters(original, from);

    size_t old_size = strlen(from);
    size_t new_size = strlen(to);
    size_t new_total_length = strlen(original) - substring_count * old_size + substring_count * new_size;

    size_t divided_size = 0;
    char **divided = string_split(original, from, &divided_size);

    if (divided == NULL) {
        return NULL;
    }

    char *result = malloc(new_total_length + 1);

    if (result == NULL) {
        return NULL;
    }

    char *append_position = result;
    for (size_t i = 0; i < divided_size; i++) {

        strcpy(append_position, divided[i]);
        append_position += strlen(divided[i]);

        if (i != divided_size - 1) {
            strcpy(append_position, to);
            append_position += strlen(to);
        }
    }
    result[new_total_length] = 0;

    return result;
}
