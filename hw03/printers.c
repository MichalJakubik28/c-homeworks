#include "printers.h"

#include "input_handling.h"
#include "linked_list_utils.h"
#include "filters.h"

#include <assert.h>
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void print_container(container_t *container1)
{
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
    printf(", Neighbors:");

    cn_node_t *neighbor = container1->neighbors->head;
    while (neighbor != NULL) {
        if (neighbor == container1->neighbors->head) {
            putchar(' ');
        }
        cn_node_t *next = neighbor->next;
        printf("%u", neighbor->container->id);
        if (next != NULL) {
            putchar(' ');
        }
        neighbor = next;
    }
    putchar('\n');
}

char *waste_to_long_form(char letter)
{
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

void print_all_containers(c_list_t *containers)
{
    c_node_t *node = containers->head;
    while (node != NULL) {
        c_node_t *next = node->next;
        print_container(node->container);
        node = next;
    }
}

void print_filtered_containers(c_list_t *containers, char waste_types[7], unsigned int capacity[2], bool public, bool filters[3])
{
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

void print_sites(s_list_t *sites)
{
    assert(sites != NULL);

    s_node_t *node = sites->head;
    unsigned int counter = 1;

    while (node != NULL) {
        s_node_t *next = node->next;
        printf("%d;", counter);
        print_waste_types(node->site->waste_types);
        putchar(';');
        print_site_neighbors(node->site);
        putchar('\n');

        counter++;
        node = next;
    }
}

void print_waste_types(char *waste_types)
{
    const char *sorted_types = "APBGCT";
    for (int i = 0; i < 6; i++) {
        if (strchr(waste_types, sorted_types[i])) {
            putchar(sorted_types[i]);
        }
    }
}

void print_site_neighbors(site_t *site)
{
    sn_node_t *site_node = site->neighbors->head;

    while (site_node != NULL) {
        sn_node_t *next = site_node->next;

        if (site_node != site->neighbors->head) {
            putchar(',');
        }
        printf("%d", site_node->site->id);

        site_node = next;
    }
}

bool print_dijkstra(site_t *site, unsigned int path_length)
{
    if (path_length == 0) {
        printf("No path between specified sites\n");
        return true;
    }

    unsigned int *output = calloc(path_length, sizeof(unsigned int));
    if (output == NULL) {
        return false;
    }

    unsigned int index = path_length - 1;
    output[index] = site->id;
    site_t *prev = site->predecessor;
    while (prev != NULL) {
        index--;
        output[index] = prev->id;
        prev = prev->predecessor;
    }

    while (index < path_length) {
        if (index != 0) {
            putchar('-');
        }
        printf("%d", output[index]);
        index++;
    }
    printf(" %d\n", site->shortest_distance);
    free(output);
    return true;
}
