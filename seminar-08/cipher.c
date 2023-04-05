#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Do *NOT* use ‹readline()› in this exercise! It will not work as you expect.
// #include "readline.h"

#define UNUSED(VAR) \
    ((void) (VAR))

/**
 * Reads 512 binary bytes from \p key and uses it as key to "encrypt"
 * each block of 512 from \p in. Resulting blocks are written to \p out.
 *
 * @param   key         the file to read key from
 * @param   in          input file
 * @param   out         output file
 * @return  0 on success, an arbitrary error code on failure
 */
int xorcrypt(FILE *key, FILE *in, FILE *out)
{
    char *key_array[512];
    fread(key_array, 1, 512, key);

    char *plaintext[512];
    unsigned int length = fread(plaintext, 1, 512, in);
    for (unsigned int index = length; index < 512; index++) {
        plaintext[index] = 0;
    }


    // TODO: implement the function
    // 1) read the key to a 512 byte long buffer using ‹fread()›
    // 2) read 512 byte blocks from ‹in› file
    // 3) for each such block use the xor operator ‹^› (caret) to encrypt
    //    each byte of the block with the respective byte in the ‹key› block
    // 4) write the modified block to the ‹out› file
    //
    // Note that the last block may be smaller than 512 bytes.
    // You sould take this into account when implementing this function.

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s KEY INPUT OUTPUT\n", argv[0]);
        return EXIT_FAILURE;
    }

    // TODO: open files

    // TODO: call ‹xorcrypt()›

    // TODO: close files

    return EXIT_SUCCESS;
}
