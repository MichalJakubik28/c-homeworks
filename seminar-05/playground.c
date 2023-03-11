#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_library.h"

void play_split(void)
{
    const char *original = "Ahoj svet 000 Query";
    char result[50][256];
    size_t size;
    char delim = ' ';

    string_split(original, result, &size, delim);
    printf("SPLIT: \nSize: %zu\nParts: \n", size);
    for (size_t i = 0; i < size; i++) {
        printf("   %zu. - %s\n", i + 1, result[i]);
    }
}

int main(void)
{
    puts("PlayGround!");
    play_split();

    return 0;
}
