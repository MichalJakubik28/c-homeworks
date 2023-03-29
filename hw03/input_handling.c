#include "input_handling.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_ERROR (-1)
#define LISTING 0
#define FILTER 1
#define CLUSTER 2
#define GRAPH 3

int decide_mode(int argc, char *argv[]) {
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
            if (i == argc - 3) {
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

bool validate_graph(char *argv[], unsigned int nodes[2]) {
    assert(strcmp(argv[1], "-g") == 0);
    return split_and_parse_values(argv[2], nodes, ',');
}

bool validate_filtering(int argc, char *argv[], char *types, unsigned int capacity[2], bool *public) {
    for (int i = 0; i < argc - 2; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (!parse_types(argv[i + 1], types)) {
                return false;
            }
            i++;
        }

        else if (strcmp(argv[i], "-c") == 0) {
            if (!split_and_parse_values(argv[i + 1], capacity, '-')) {
                return false;
            }
            i++;
        }

        else if (strcmp(argv[i], "-p") == 0) {
            if (!parse_accessibility(argv[i + 1], public)) {
                return false;
            }
            i++;
        }
    }
    return true;
}

bool parse_types(char *input, char *types) {
    for (unsigned int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
        case 'A':
            *types = (char) (*types | plastics_aluminium);
            break;
        case 'P':
            *types = (char) (*types | paper);
            break;
        case 'B':
            *types = (char) (*types | biodegradable_waste);
            break;
        case 'G':
            *types = (char) (*types | clear_glass);
            break;
        case 'C':
            *types = (char) (*types | colored_glass);
            break;
        case 'T':
            *types = (char) (*types | textile);
            break;
        default:
            return INPUT_ERROR;
        }
    }

    return true;
}

bool split_and_parse_values(char input[], unsigned int values[2], int delimiter) {
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

//        printf("Number: %ld Not parsed: %s\n", value_long, unparsed);
        if (unparsed[0] != 0 || value_long >= UINT_MAX) {
            return false;
        }

        values[i] = value_long;
        i++;
    }
    return true;
}

bool parse_accessibility(char *input, bool *public) {
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
