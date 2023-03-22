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
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(rows);
    /* ! */ UNUSED(row_sizes);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
}

int dyn_free2d(void **memory, size_t rows)
{
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(rows);
    /* ! */ UNUSED(memory);
    /* ! */ NOT_IMPLEMENTED();
    return 1;
}

/**
 * BONUSES
 */

unsigned **pascal_triangle(size_t depth)
{
    /* ! */ UNUSED(depth);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
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
