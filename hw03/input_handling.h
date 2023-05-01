#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H

#include <stdbool.h>

#define INPUT_OK 0
#define INPUT_ERROR (-1)
#define LISTING 0
#define FILTER 1
#define CLUSTER 2
#define GRAPH 3
#define FILTER_NOT_USED 0
#define FILTER_USED 1

/**
 * @brief Parses accessibility string from command line.
 *
 * @param input string from command line with information about accessibility
 * @param public pointer to a place where parsed value should be stored
 * @retval true if input could be parsed, else false
 */
bool parse_accessibility(char *input, bool *public);

/**
 * @brief Splits string by delimiter and parses substrings as unsigned integers.
 *
 * @param input string from command line with two integers separated by a delimiter
 * @param values array where parsed integers should be stored
 * @param delimiter delimiter of values
 * @retval true if input could be parsed, else false
 */
bool split_and_parse_values(char *input, unsigned int values[2], int delimiter);

/**
 * @brief Parses waste types string from command line.
 *
 * @param input string from command line with information about waste types
 * @param types pointer to a place where parsed types should be stored
 * @retval true if input could be parsed, else false
 */
bool parse_types(char *input, char *types);

/**
 * @brief Validates shortest path input parameters from command line.
 *
 * @param argv command line arguments
 * @param nodes array of numbers where parsed node ids should be stored
 * @retval true if input could be parsed, else false
 */
bool validate_graph(char *argv[], unsigned int nodes[2]);

/**
 * @brief Decides which task is being executed based on switches.
 *
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @retval task macro value or INPUT_ERROR if conflicting or invalid command line input was received
 */
int decide_mode(int argc, char *argv[]);

/**
 * @brief Validates and parses accessibility switch argument on command line.
 *
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @param public pointer to a place where parsed value should be stored
 * @retval integer macro value based on whether filter is used or not or
 * INPUT_ERROR if conflicting or invalid command line input was received
 */
int validate_accessibility(int argc, char *argv[], bool *public);

/**
 * @brief Validates and parses capacity switch argument on command line.
 *
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @param capacity pointer to an array where parsed values should be stored
 * @retval integer macro value based on whether filter is used or not or
 * INPUT_ERROR if conflicting or invalid command line input was received
 */
int validate_capacity(int argc, char *argv[], unsigned int capacity[2]);

/**
 * @brief Validates and parses waste types switch argument on command line.
 *
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @param types pointer to an array where parsed waste types should be stored
 * @retval integer macro value based on whether filter is used or not or
 * INPUT_ERROR if conflicting or invalid command line input was received
 */
int validate_waste_types(int argc, char *argv[], char *types);

/**
 * @brief Adds waste type to an array of waste types.
 *
 * @param input waste type initial
 * @param types array of waste types
 *
 */
void add_to_types(char input, char *types);

#endif //INPUT_HANDLING_H
