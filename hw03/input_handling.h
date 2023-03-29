#ifndef HW03_INPUT_HANDLING_H
#define HW03_INPUT_HANDLING_H

#include <stdbool.h>

enum trash_t {
    plastics_aluminium = 1 << 5,
    paper = 1 << 4,
    biodegradable_waste = 1 << 3,
    clear_glass = 1 << 2,
    colored_glass = 1 << 1,
    textile = 1
};

bool parse_accessibility(char *input, bool *public);
bool split_and_parse_values(char input[], unsigned int values[2], int delimiter);
bool parse_types(char *input, char *types);
bool validate_filtering(int argc, char *argv[], char *types, unsigned int capacity[2], bool *public);
bool validate_graph(char *argv[], unsigned int nodes[2]);
int decide_mode(int argc, char *argv[]);

#endif //HW03_INPUT_HANDLING_H
