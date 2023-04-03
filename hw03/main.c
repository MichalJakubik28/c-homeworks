#include "container_loading.h"
#include "data_source.h"
#include "input_handling.h"
#include "linked_list_utils.h"
#include "paths_loading.h"
#include "sites_processing.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool assess_filter_validation(int return_code, bool *filters, int index);
void print_container(container_t *container1);
char *waste_to_long_form(char letter);
void print_all_containers(c_list_t *containers);
void print_filtered_containers(c_list_t *containers, char waste_types[7], unsigned int capacity[2], bool public, bool filters[3]);
bool filter_waste_type(container_t *container1, bool filter_used, char waste_types[7]);
bool filter_capacity(container_t *container1, bool filter_used, const unsigned int capacity[2]);
bool filter_accessibility(container_t *container1, bool filter_used, bool public);
void print_sites(s_list_t *sites);
void print_waste_types(char *waste_types);

int main(int argc, char *argv[])
{
    // input parsing and validation
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
    c_list_t *containers;
    containers = load_containers();
    if (containers == NULL) {
        destroy_data_source();
        return EXIT_FAILURE;
    }

    // copy paths info from parser
    if (!load_paths(containers)) {
        printf("Paths NOK, freeing memory\n");
        destroy_containers(containers);
        destroy_data_source();
        return EXIT_FAILURE;
    }

    destroy_data_source();

    if (mode == GRAPH) {
        unsigned int nodes[] = {0, 0};
        if (!validate_graph(argv, nodes)) {
            fprintf(stderr, "Invalid -g argument\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }
        printf("NOT IMPLEMENTED YET");
        destroy_containers(containers);
        return EXIT_FAILURE;
    }

    else if (mode == FILTER) {
        // whether filters are used: waste types, capacity, accessibility
        bool filters[3] = {false, false, false};

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
//        printf("Used filters: ");
//        if (filters[0]) {
//            printf("Waste types: %s ", waste_types);
//        }
//        if (filters[1]) {
//            printf("Capacity: %d - %d ", capacity[0], capacity[1]);
//        }
//        if (filters[2]) {
//            printf("Public: %c\n", public ? 'Y' : 'N');
//        }

    }

    else if (mode == CLUSTER) {
        s_list_t *sites = assign_sites_to_containers(containers);
        if (sites == NULL) {
            fprintf(stderr, "Could not create sites\n");
            destroy_containers(containers);
            return EXIT_FAILURE;
        }
        print_sites(sites);
        destroy_sites(sites);
    }

    else {
        print_all_containers(containers);
    }

    destroy_containers(containers);

    return EXIT_SUCCESS; // May your program be as successful as this macro. Good luck!
}

bool assess_filter_validation(int return_code, bool *filters, int index) {
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

void print_container(container_t *container1) {
    printf("ID: %d, Type: %s, Capacity: %d, Address:",
            container1->id,
            waste_to_long_form(container1->waste_type),
            container1->capacity);

    if (strlen(container1->street) > 0) {
        printf(" %s", container1->street);
    }

    if (container1->number != UINT_MAX) {
        printf(" %d", container1->number);
    }

    // print neighbors
    printf(", Neighbors: ");

    cn_node_t *neighbor = container1->neighbors->head;
    while (neighbor != NULL) {
        cn_node_t *next = neighbor->next;
        printf("%u", neighbor->container->id);
        if (next != NULL) {
            putchar(' ');
        }
        neighbor = next;
    }
    putchar('\n');
}

char *waste_to_long_form(char letter) {
    switch (letter) {
    case 'A':
        return "Plastics and Aluminium";
    case 'P':
        return "Paper";
    case 'B':
        return "Biodegradable waste";
    case 'G':
        return "Clear glass";
    case 'C':
        return "Colored glass";
    case 'T':
        return "Textile";
    default:
        return NULL;
    }
}

void print_all_containers(c_list_t *containers) {
    c_node_t *node = containers->head;
    while (node != NULL) {
        c_node_t *next = node->next;
        print_container(node->container);
        node = next;
    }
}

void print_filtered_containers(c_list_t *containers, char waste_types[7], unsigned int capacity[2], bool public, bool filters[3]) {
    c_node_t *node = containers->head;

    while (node != NULL) {
        c_node_t *next = node->next;
        if (filter_waste_type(node->container, filters[0], waste_types) &&
                filter_capacity(node->container, filters[1], capacity) &&
                filter_accessibility(node->container, filters[2], public)) {
            print_container(node->container);
        }
        node = next;
    }
}

bool filter_waste_type(container_t *container1, bool filter_used, char waste_types[7]) {
    assert(container1 != NULL);
    return !filter_used || strchr(waste_types, container1->waste_type) != NULL;
}

bool filter_capacity(container_t *container1, bool filter_used, const unsigned int capacity[2]) {
    assert(container1 != NULL);
    return !filter_used || (container1->capacity >= capacity[0] && container1->capacity <= capacity[1]);
}

bool filter_accessibility(container_t *container1, bool filter_used, bool public) {
    return !filter_used || container1->public == public;
}

void print_sites(s_list_t *sites) {
    assert(sites != NULL);

    s_node_t *node = sites->head;
    unsigned int counter = 1;

    while (node != NULL) {
        s_node_t *next = node->next;
        printf("%d;", counter);
        print_waste_types(node->waste_types);
        printf(";[tu budu susedia]");
        putchar('\n');

        counter++;
        node = next;
    }
}

void print_waste_types(char *waste_types){
    const char *sorted_types = "APBGCT";
    for (int i = 0; i < 6; i++) {
        if (strchr(waste_types, sorted_types[i])) {
            putchar(sorted_types[i]);
        }
    }
}
