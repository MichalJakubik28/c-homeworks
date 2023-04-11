#include "container_loading.h"
#include "data_source.h"
#include "dijkstra.h"
#include "input_handling.h"
#include "linked_list_utils.h"
#include "paths_loading.h"
#include "printers.h"
#include "sites_processing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool assess_filter_validation(int return_code, bool *filters, int index);

int main(int argc, char *argv[])
{
    // decide on mode based on command line switches
    int mode = decide_mode(argc, argv);

    if (mode == INPUT_ERROR) {
        fprintf(stderr, "Could not parse input - invalid or not enough arguments\n");
        return EXIT_FAILURE;
    }

    // copy data from parser to structures

    // initialize data source
    if (!init_data_source(argv[argc - 2], argv[argc - 1])) {
        fprintf(stderr, "Could not initialize files\n");
        return EXIT_FAILURE;
    }

    // copy containers info from parser
    c_list_t *containers = load_containers();
    if (containers == NULL) {
        fprintf(stderr, "Could not load containers\n");
        destroy_data_source();
        return EXIT_FAILURE;
    }

    // copy paths info from parser
    if (!load_paths(containers)) {
        fprintf(stderr, "Could not load paths\n");
        destroy_containers(containers);
        destroy_data_source();
        return EXIT_FAILURE;
    }

    // data source no longer needed, can be destroyed
    destroy_data_source();

    if (mode == FILTER) {
        // whether filters are used: waste types, capacity, accessibility
        bool filters[3] = { false, false, false };

        char waste_types[7];
        memset(waste_types, 0, 7);
        if (!assess_filter_validation(validate_waste_types(argc, argv, waste_types), filters, 0)) {
            fprintf(stderr, "Invalid waste type filter parameter\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }

        unsigned int capacity[2];
        memset(capacity, 0, sizeof(unsigned int) * 2);
        if (!assess_filter_validation(validate_capacity(argc, argv, capacity), filters, 1)) {
            fprintf(stderr, "Invalid capacity filter parameter\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }

        bool public = false;
        if (!assess_filter_validation(validate_accessibility(argc, argv, &public), filters, 2)) {
            fprintf(stderr, "Invalid accessibility filter parameter\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }

        print_filtered_containers(containers, waste_types, capacity, public, filters);
    }

    else if (mode == CLUSTER || mode == GRAPH) {
        // both clustering and shortest path need to create sites first
        s_list_t *sites = assign_sites_to_containers(containers);
        if (sites == NULL) {
            fprintf(stderr, "Could not create sites\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }
        if (!assign_neighbors_to_sites(containers)) {
            fprintf(stderr, "Could not link sites together\n");
            destroy_sites(sites);
            destroy_containers(containers);
            return EXIT_FAILURE;
        }

        if (mode == CLUSTER) {
            print_sites(sites);
        } else {
            // on top of sites, shortest path also needs to run dijkstra on the sites graph
            unsigned int nodes[] = { 0, 0 };
            // validate command line arguments of the task (syntax only)
            if (!validate_graph(argv, nodes)) {
                fprintf(stderr, "Invalid -g argument\n");
                destroy_sites(sites);
                destroy_containers(containers);
                return EXIT_FAILURE;
            }

            // run dijkstra on graph
            site_t *target = NULL;
            int result = dijkstra(sites, nodes[0], nodes[1], &target);
            if (!result) {
                fprintf(stderr, "Invalid start or target point\n");
                destroy_sites(sites);
                destroy_containers(containers);
                return EXIT_FAILURE;
            }

            unsigned int length = path_length(target);

            // print found path
            if (!print_dijkstra(target, length)) {
                fprintf(stderr, "Could not allocate memory for path printing\n");
                destroy_sites(sites);
                destroy_containers(containers);
                return EXIT_FAILURE;
            }

        }

        destroy_sites(sites);

    }

    else {
        print_all_containers(containers);
    }

    destroy_containers(containers);

    return EXIT_SUCCESS;
}

bool assess_filter_validation(int return_code, bool *filters, int index)
{
    switch (return_code) {
    case FILTER_USED:
        filters[index] = true;
        return true;
    case INPUT_ERROR:
        return false;
    default:
        return true;
    }
}
