#include "input_handling.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int decide_mode(int argc, char *argv[])
{
    if (argc < 3) {
        return INPUT_ERROR;
    }

    bool s = false;
    bool t = false;
    bool c = false;
    bool p = false;
    bool g = false;

    for (int i = 1; i < argc - 2; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (s || t || g) {
                return INPUT_ERROR;
            }
            if (i == argc - 3) {
                return INPUT_ERROR;
            }

            t = true;
            i++;
        }

        else if (strcmp(argv[i], "-c") == 0) {
            if (s || c || g) {
                return INPUT_ERROR;
            }
            if (i == argc - 3) {
                return INPUT_ERROR;
            }

            c = true;
            i++;
        }

        else if (strcmp(argv[i], "-p") == 0) {
            if (s || p || g) {
                return INPUT_ERROR;
            }
            if (i == argc - 3) {
                return INPUT_ERROR;
            }

            p = true;
            i++;
        }

        else if (strcmp(argv[i], "-g") == 0) {
            if (s || c || t || p || g) {
                return -1;
            }
            if (i == argc - 3) {
                return INPUT_ERROR;
            }

            g = true;
            i++;
        }

        else if (strcmp(argv[i], "-s") == 0) {
            if (s || c || t || p || g) {
                return INPUT_ERROR;
            }

            s = true;
        }

        else {
            return INPUT_ERROR;
        }
    }

    if (!(s || c || t || p || g)) {
        return LISTING;
    }

    if (t || c || p) {
        return FILTER;
    }

    if (s) {
        return CLUSTER;
    }

    return GRAPH;
}

bool validate_graph(char *argv[], unsigned int nodes[2])
{
    assert(strcmp(argv[1], "-g") == 0);
    return split_and_parse_values(argv[2], nodes, ',');
}

int validate_waste_types(int argc, char *argv[], bool *types)
{
    for (int i = 1; i < argc - 2; i += 2) {
        if (strcmp(argv[i], "-t") == 0) {
            if (!parse_types(argv[i + 1], types)) {
                return INPUT_ERROR;
            }
            return FILTER_USED;
        }
    }
    return FILTER_NOT_USED;
}

int validate_capacity(int argc, char *argv[], unsigned int capacity[2])
{
    for (int i = 1; i < argc - 2; i += 2) {
        if (strcmp(argv[i], "-c") == 0) {
            if (!split_and_parse_values(argv[i + 1], capacity, '-')) {
                return INPUT_ERROR;
            }
            if (capacity[1] < capacity[0]) {
                return INPUT_ERROR;
            }
            return FILTER_USED;
        }
    }
    return FILTER_NOT_USED;
}

int validate_accessibility(int argc, char *argv[], bool *public)
{
    for (int i = 1; i < argc - 2; i += 2) {
        if (strcmp(argv[i], "-p") == 0) {
            if (!parse_accessibility(argv[i + 1], public)) {
                return INPUT_ERROR;
            }
            return FILTER_USED;
        }
    }
    return FILTER_NOT_USED;
}

void add_to_types(enum waste_types input, bool *types)
{
    types[input - 1] = true;
    //    for (int i = 0; i < 6; i++) {
    //        if (types[i] == input) {
    //            return;
    //        }
    //        if (types[i] == 0) {
    //            types[i] = input;
    //            return;
    //        }
    //    }
}

bool parse_types(char *input, bool *types)
{
    for (unsigned int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
        case 'A':
        case 'P':
        case 'B':
        case 'G':
        case 'C':
        case 'T':
            add_to_types(char_to_enum(input[i]), types);
            break;
        default:
            return false;
        }
    }

    return true;
}

bool split_and_parse_values(char *input, unsigned int values[2], int delimiter)
{
    char *delim = strchr(input, delimiter);
    if (delim == NULL) {
        return false;
    }
    unsigned long value_length = delim - input;

    for (int i = 0; i < 2; value_length = strlen(input) - value_length - 1) {
        char value[value_length + 1];
        memset(value, 0, value_length + 1);
        strncpy(value, input + i * (delim - input + 1), value_length);
        char *unparsed = 0;
        unsigned long value_long = strtol(value, &unparsed, 10);

        if (unparsed[0] != 0 || value_long >= UINT_MAX) {
            return false;
        }

        values[i] = value_long;
        i++;
    }
    return true;
}

bool parse_accessibility(char *input, bool *public)
{
    if (strcmp(input, "Y") == 0) {
        *public = true;
        return true;
    }

    if (strcmp(input, "N") == 0) {
        *public = false;
        return true;
    }

    return false;
}

int char_to_enum(char input)
{
    switch (input) {
    case 'A':
        return PLASTICS_AND_ALUMINIUM;
    case 'P':
        return PAPER;
    case 'T':
        return TEXTILE;
    case 'C':
        return COLORED_GLASS;
    case 'G':
        return CLEAR_GLASS;
    case 'B':
        return BIODEGRADABLE_WASTE;
    default:
        return -1;
    }
}

char enum_to_char(char input)
{
    switch (input) {
    case PLASTICS_AND_ALUMINIUM:
        return 'A';
    case PAPER:
        return 'P';
    case TEXTILE:
        return 'T';
    case COLORED_GLASS:
        return 'C';
    case CLEAR_GLASS:
        return 'G';
    case BIODEGRADABLE_WASTE:
        return 'B';
    default:
        return 'X';
    }
}
