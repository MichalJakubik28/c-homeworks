#include "container_loading.h"

#include "data_source.h"
#include "input_handling.h"
#include "linked_list_utils.h"

#include <limits.h>
#include <stdbool.h>
#include <string.h>

void destroy_container(container_t *container)
{
    if (container == NULL) {
        return;
    }

    free(container->street);
    free(container->name);
    destroy_neighbors((llist *) container->neighbors);
    free(container);
}

bool parse_container_id(const char *id, container_t *container)
{
    if (id[0] == 0) {
        return false;
    }
    char *unparsed;
    long long_id = strtol(id, &unparsed, 10);
    if (unparsed[0] != 0 || long_id >= UINT_MAX || long_id < 0) {
        return false;
    }
    container->id = long_id;
    return true;
}

bool parse_container_x(const char *x, container_t *container)
{
    if (x[0] == 0) {
        return false;
    }

    char *dot = strchr(x, '.');
    if (dot != NULL && (x + strlen(x) - dot - 1 > 15)) {
        return false;
    }

    char *unparsed;
    double double_x = strtod(x, &unparsed);
    if (unparsed[0] != 0) {
        return false;
    }
    container->x = double_x;
    return true;
}

bool parse_container_y(const char *y, container_t *container)
{
    double former_x = container->x;
    if (!parse_container_x(y, container)) {
        return false;
    }
    container->y = container->x;
    container->x = former_x;
    return true;
}

bool parse_container_waste(const char *type, container_t *container)
{
    if (strcmp(type, "Plastics and Aluminium") == 0) {
        container->waste_type = char_to_enum('A');
        return true;
    }
    if (strcmp(type, "Paper") == 0) {
        container->waste_type = char_to_enum('P');
        return true;
    }
    if (strcmp(type, "Biodegradable waste") == 0) {
        container->waste_type = char_to_enum('B');
        return true;
    }
    if (strcmp(type, "Clear glass") == 0) {
        container->waste_type = char_to_enum('G');
        return true;
    }
    if (strcmp(type, "Colored glass") == 0) {
        container->waste_type = char_to_enum('C');
        return true;
    }
    if (strcmp(type, "Textile") == 0) {
        container->waste_type = char_to_enum('T');
        return true;
    }
    return false;
}

bool parse_container_capacity(const char *capacity, container_t *container)
{
    if (capacity[0] == 0) {
        return false;
    }
    char *unparsed;
    long long_capacity = strtol(capacity, &unparsed, 10);
    if (unparsed[0] != 0 || long_capacity >= UINT_MAX || long_capacity < 0) {
        return false;
    }
    container->capacity = long_capacity;
    return true;
}

bool parse_container_name(const char *name, container_t *container)
{
    size_t length = strlen(name);
    char *parsed_name = calloc(length + 1, sizeof(char));
    if (parsed_name == NULL) {
        return false;
    }
    strncpy(parsed_name, name, length);
    container->name = parsed_name;

    return true;
}

bool parse_container_address(const char *address, container_t *container)
{
    char *former_name = container->name;
    if (!parse_container_name(address, container)) {
        return false;
    }
    container->street = container->name;
    container->name = former_name;
    return true;
}

bool parse_container_number(const char *number, container_t *container)
{
    if (strlen(number) == 0) {
        container->number = UINT_MAX;
        return true;
    }
    char *unparsed;
    long long_number = strtol(number, &unparsed, 10);
    if (unparsed[0] != 0 || long_number >= UINT_MAX || long_number < 0) {
        return false;
    }
    container->number = long_number;
    return true;
}

bool parse_container_public(const char *public, container_t *container)
{
    if (strlen(public) != 1) {
        return false;
    }

    switch (public[0]) {
    case 'Y':
        container->public = true;
        return true;
    case 'N':
        container->public = false;
        return true;
    default:
        return false;
    }
}

container_t *create_container(size_t line)
{
    container_t *p_container = malloc(sizeof(container_t));

    if (p_container == NULL) {
        return NULL;
    }
    p_container->name = NULL;
    p_container->street = NULL;
    p_container->neighbors = NULL;
    p_container->site = NULL;

    const char *(*get_param[])(size_t) = {
        &get_container_id,
        &get_container_x,
        &get_container_y,
        &get_container_waste_type,
        &get_container_capacity,
        &get_container_name,
        &get_container_street,
        &get_container_number,
        &get_container_public
    };
    bool (*parse_param[])(const char *, container_t *) = {
        &parse_container_id,
        &parse_container_x,
        &parse_container_y,
        &parse_container_waste,
        &parse_container_capacity,
        &parse_container_name,
        &parse_container_address,
        &parse_container_number,
        &parse_container_public
    };

    for (int i = 0; i < 9; i++) {
        if (!parse_param[i](get_param[i](line), p_container)) {
            destroy_container(p_container);
            return NULL;
        }
    }

    cn_list_t *neighbours = malloc(sizeof(cn_list_t));
    if (neighbours == NULL) {
        destroy_container(p_container);
        return NULL;
    }
    list_init((llist *) neighbours);
    p_container->neighbors = neighbours;
    return p_container;
}

c_list_t *load_containers(void)
{
    unsigned int line = 0;
    c_list_t *containers = malloc(sizeof(c_list_t));
    if (containers == NULL) {
        return NULL;
    }
    list_init((llist *) containers);
    while (get_container_id(line) != NULL) {
        container_t *container = create_container(line);

        if (container == NULL || c_get_by_id(containers, container->id) != NULL) {
            destroy_container(container);
            destroy_containers(containers);
            return NULL;
        }

        c_node_t *container_node = create_c_node(container);
        if (container_node == NULL) {
            destroy_container(container);
            destroy_containers(containers);
            return NULL;
        }

        list_append((llist *) containers, (ll_node *) container_node);
        line++;
    }
    return containers;
}
