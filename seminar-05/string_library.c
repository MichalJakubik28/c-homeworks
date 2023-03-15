#include "string_library.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "assert.h"

#define UNUSED(param) ((void) (param))
#define NOT_IMPLEMENTED()                                                   \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        raise(SIGTERM);                                                     \
    } while (0)

size_t string_length(const char *str)
{
    if (str == NULL) {
        return 0;
    }
    size_t index = 0;
    while (1) {
        char letter = str[index];
        if (letter == 0) {
            return index;
        }
        index += 1;
    }
}

char *string_copy(char *result, const char *original)
{
    if (result == NULL || original == NULL) {
        return NULL;
    }
    int index = 0;
    while (original[index] != 0) {
        result[index] = original[index];
        index += 1;
    }
    result[index] = '\0';
    return result;
}

size_t string_count_char(const char *string, char ch)
{
    if (string == NULL || ch == 0) {
        return 0;
    }
    int index = 0;
    int counter = 0;
    while (string[index] != 0) {
        if (string[index] == ch) {
            counter++;
        }
        index += 1;
    }
    return counter;
}

char *string_edit(char (*fn)(char), char *string)
{
    if (fn == NULL || string == NULL) {
        return NULL;
    }
    size_t index = 0;
    while (string[index] != '\0') {
        string[index] = fn(string[index]);
        index += 1;
    }
    return string;
}

size_t string_count_substr(const char *original, const char *substring)
{
    if (original == NULL || substring == NULL) {
        return 0;
    }
    if (original[0] == '\0' || substring[0] == '\0') {
        return 0;
    }
    size_t counter = 0;
    char *last_match;
    do {
        last_match = strstr(original, substring);
        original = last_match + 1;
        counter += 1;
    }
    while (last_match != NULL);
    counter--;

    return counter;
}

size_t string_count_string_in_array(const char **array, const char *string)
{
    if (array == NULL || string == NULL) {
        return 0;
    }
    size_t count = 0;
    size_t index = 0;
    while (array[index] != NULL) {
        int same = strcmp(array[index], string);
        if (same == 0) {
            count++;
        }
        index++;
    }
    return count;
}

void string_split(const char *original, char result[50][256], size_t *size, char delim)
{
    if (original == NULL || size == NULL || result == NULL) {
        return;
    }
    int counter = 0;
    const char *start = original;
    char *nearest_delim = strchr(original, delim);
    while (nearest_delim != NULL) {
        long diff = start - nearest_delim;
        strncpy(result[counter], start, diff);
        counter += 1;
        start = nearest_delim + 1;
        nearest_delim = strchr(original, delim);
    }
}
