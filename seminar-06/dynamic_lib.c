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
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(str);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
}

char *dyn_strjoin(const char *pre, const char *post)
{
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ UNUSED(pre);
    /* ! */ UNUSED(post);
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
}

char *read_line(void)
{
    /* TODO: Remove the following lines and implement the function. */
    /* ! */ NOT_IMPLEMENTED();
    return NULL;
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
