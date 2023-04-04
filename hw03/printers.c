#include "printers.h"

#include "linked_list_utils.h"

#include <assert.h>
#include <limits.h>
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

bool filter_waste_type(container_t *container1, bool filter_used, char waste_types[7])
{
    assert(container1 != NULL);
    return !filter_used || strchr(waste_types, container1->waste_type) != NULL;
}

bool filter_capacity(container_t *container1, bool filter_used, const unsigned int capacity[2])
{
    assert(container1 != NULL);
    return !filter_used || (container1->capacity >= capacity[0] && container1->capacity <= capacity[1]);
}

bool filter_accessibility(container_t *container1, bool filter_used, bool public)
{
    return !filter_used || container1->public == public;
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
