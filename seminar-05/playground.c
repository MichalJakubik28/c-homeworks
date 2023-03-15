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

    printf("%lu\n", string_count_substr("PESPESP", "PESP"));
    printf("HEEJ");
//    const char *original = "Ahoj svet 000 Query";
//    char result[50][256];
//    size_t size;
//    char delim = ' ';
//
//    string_split(original, result, &size, delim);
//    printf("SPLIT: \nSize: %zu\nParts: \n", size);
//    for (size_t i = 0; i < size; i++) {
//        printf("   %zu. - %s\n", i + 1, result[i]);
//    }
}

int main(void)
{
    puts("PlayGround!");
    play_split();

    return 0;
}
