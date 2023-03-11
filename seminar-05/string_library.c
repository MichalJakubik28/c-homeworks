#include "string_library.h"

#include <signal.h>
#include <stdio.h>

#include "assert.h"

#define UNUSED(param) ((void) (param))
#define NOT_IMPLEMENTED()                                                   \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        raise(SIGTERM);                                                     \
    } while (0)

size_t string_length(const char *str)
{
    // TODO
    UNUSED(str);
    NOT_IMPLEMENTED();
    return 0;
}

char *string_copy(char *result, const char *original)
{
    // TODO
    UNUSED(result);
    UNUSED(original);
    NOT_IMPLEMENTED();
    return NULL;
}

size_t string_count_char(const char *string, char ch)
{
    // TODO
    UNUSED(string);
    UNUSED(ch);
    NOT_IMPLEMENTED();
    return 0;
}

char *string_edit(char (*fn)(char), char *string)
{
    // TODO
    UNUSED(fn);
    UNUSED(string);
    NOT_IMPLEMENTED();
    return NULL;
}

size_t string_count_substr(const char *original, const char *substring)
{
    // TODO
    UNUSED(original);
    UNUSED(substring);
    NOT_IMPLEMENTED();
    return 0;
}

size_t string_count_string_in_array(const char **array, const char *string)
{
    //TODO
    UNUSED(array);
    UNUSED(string);
    NOT_IMPLEMENTED();
    return 0;
}

void string_split(const char *original, char result[50][256], size_t *size, char delim)
{
    // TODO
    UNUSED(original);
    UNUSED(result);
    UNUSED(size);
    UNUSED(delim);
    NOT_IMPLEMENTED();
}
