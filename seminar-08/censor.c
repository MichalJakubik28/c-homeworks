#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readline.h"

#define UNUSED(VAR) \
    ((void) (VAR))

/**
 * Searches for \p search in each line of \p in and replaces it with
 * stars. The result is written into \p out.
 *
 * \param   search      string to censor
 * \param   in          input file
 * \param   out         output file
 * \return  0 on success, an arbitrary error code on failure
 */
int censor(const char *search, FILE *in, FILE *out)
{
    char *line = readline(in);
    while (line != NULL) {
        char *to_censor = strstr(line, search);
        char *last_printed = line;

        while (to_censor != NULL) {
            while (last_printed != to_censor) {
                putc(*last_printed, out);
                last_printed++;
            }
            for (unsigned int i = 0; i < strlen(search); i++) {
                putc('*', out);
                last_printed++;
            }
            to_censor = strstr(last_printed, search);
        }
        fprintf(out, "%s", last_printed);
        free(line);
        line = readline(in);
    }

    // TODO: implement the function

    // 1) use one loop to iterate over lines using ‹readline()›
    // 2) use another loop to search for all occurences of ‹search›
    //    using the ‹strstr()› function
    // 3) write the modified line to the ‹out› file

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s STRING SOURCE DESTINATION\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *in = fopen(argv[2], "r");
    if (in == NULL) {
        fprintf(stderr, "Could not open input file\n");
    }

    FILE *out = fopen(argv[3], "w");
    if (out == NULL) {
        fprintf(stderr, "Could not open output file\n");
    }

    censor(argv[1], in, out);
    fclose(in);
    fclose(out);
    // TODO: open input and output file

    // TODO: call ‹censor()›

    // TODO: close files

    return EXIT_SUCCESS;
}
