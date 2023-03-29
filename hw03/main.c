#include <stdio.h>
#include <stdlib.h>

// TODO: [Optional] Think about an appropriate division of the solution into files.
//                  e.g. Move data loading and validating to another .c file.

#include "data_source.h" // TODO: Read the content of this file.
#include "input_handling.h"
#include "data_handling.h"
#define INPUT_ERROR (-1)
#define LISTING 0
#define FILTER 1
#define CLUSTER 2
#define GRAPH 3


int main(int argc, char *argv[])
{
    testZasobnik();
    // input parsing and validation
    int mode = decide_mode(argc, argv);
    printf("Mode: %d\n", mode);

    if (mode == INPUT_ERROR) {
        fprintf(stderr, "Could not parse input - invalid or not enough arguments\n");
        return EXIT_FAILURE;
    }

    if (mode == GRAPH) {
        unsigned int nodes[] = {0, 0};
        if (!validate_graph(argv, nodes)) {
            fprintf(stderr, "Invalid -g argument\n");
            return EXIT_FAILURE;
        }
    }

    else if (mode == FILTER) {
        char trash_types = 0;
        unsigned int capacity[2];
        bool public;
        if (!validate_filtering(argc, argv, &trash_types, capacity, &public)) {
            fprintf(stderr, "Invalid arguments for -t, -c or -p");
            return EXIT_FAILURE;
        }
        printf("Filtering: trash types: %hd, capacity: %d - %d, public: %c", trash_types, capacity[0], capacity[1], (public ? 'Y' : 'N'));
    }

    if (!init_data_source(argv[argc - 2], argv[argc - 1])) {
        fprintf(stderr, "Could not initialize files\n");
        return EXIT_FAILURE;
    }

    printf("OK\n");
    container_t **containers;
    containers = load_and_validate();
    destroy_data_source();
    printf("ALLES OK\n");

    // TODO: Read and validate options.

    // This is only a demo, you should probably move the following line somewhere else.
    //init_data_source("path/to/containers/file.csv", "path/to/paths/file.csv");

    // TODO: Save data to your own structures.

    //destroy_data_source(); // If you forget to do this, Valgrind will yell at you a lot.

    // TODO: Process the data as the user wishes and print them to the stdin.

    return EXIT_SUCCESS; // May your program be as successful as this macro. Good luck!
}
