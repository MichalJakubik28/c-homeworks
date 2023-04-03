#ifndef HW03_INPUT_HANDLING_H
#define HW03_INPUT_HANDLING_H

#include <stdbool.h>

#define INPUT_ERROR (-1)
#define LISTING 0
#define FILTER 1
#define CLUSTER 2
#define GRAPH 3
#define FILTER_NOT_USED 0
#define FILTER_USED 1

bool parse_accessibility(char *input, bool *public);
bool split_and_parse_values(char input[], unsigned int values[2], int delimiter);
bool parse_types(char *input, char *types);
bool validate_graph(char *argv[], unsigned int nodes[2]);
int decide_mode(int argc, char *argv[]);
int validate_accessibility(int argc, char *argv[], bool *public);
int validate_capacity(int argc, char *argv[], unsigned int capacity[2]);
int validate_waste_types(int argc, char *argv[], char *types);
void add_to_types(char input, char *types);

#endif //HW03_INPUT_HANDLING_H
