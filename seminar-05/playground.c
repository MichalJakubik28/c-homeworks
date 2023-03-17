#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "string_library.h"
#include "assert.h"


char edit_up(char c)
{
    return toupper(c);
}

int comparator(char a, char b)
{
    return a - b;
}

void transform_up(void *out, int i, const char ch)
{
    char *result = (char *) out;
    result[i] = toupper(ch);
}

void play_split(void)
{

    size_t length = string_length("Hello world!");
    assert(length == 12);
    char buffer[7];
    string_copy(buffer, "Hello!"); // buffer will contain string "Hello!"
    assert(strcmp(buffer, "Hello!") == 0);
    size_t count_a = string_count_char("abba123 a", 'a');

    char string[] = "Hello!";
    string_edit(&edit_up, string);
    assert(strcmp(string, "HELLO!") == 0);

    assert(string_count_substr("PESPESP", "PESP") == 2);

    char array[] = {'7','6','5','1','3','9','4', '2', '8'};
    printf("\nINSERT SORT:\nBefore sorting: %s\n", array);
    string_insert_sort(array, &comparator);
    printf("Sorted: %s\n\n", array);

    const char *original = "Ahoj svet 000 Query";
    char result[50][256];
    size_t size;
    char delim = ' ';

    string_split(original, result, &size, delim);
    printf("SPLIT: \nSize: %zu\nParts: \n", size);
    for (size_t i = 0; i < size; i++) {
        printf("   %zu. - %s\n", i + 1, result[i]);
    }

    char array2[] = "abcdef123456";
    char result2[13];
    result2[12] = 0;
    string_map(array2, result2, &transform_up);
    printf("\nString map:\nOriginal: %s\nResult: %s\n", array2, result2);
}

int main(void)
{
    puts("PlayGround!");
    play_split();

    return 0;
}
