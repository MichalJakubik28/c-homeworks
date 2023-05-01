#include "paths_loading.h"

#include "data_source.h"
#include "linked_list_utils.h"

#include <limits.h>
#include <stdbool.h>

bool string_to_uint(const char *string, unsigned int *uint)
{
    char *unparsed;
    long long_id = strtol(string, &unparsed, 10);
    if (unparsed[0] != 0 || long_id >= UINT_MAX || long_id < 0) {
        return false;
    }
    *uint = long_id;
    return true;
}

bool load_paths(c_list_t *containers)
{
    unsigned int line = 0;
    unsigned int id_a = UINT_MAX;
    unsigned int id_b = UINT_MAX;
    unsigned int distance = UINT_MAX;
    while (get_path_a_id(line) != NULL) {
        if (!string_to_uint(get_path_a_id(line), &id_a) ||
                !string_to_uint(get_path_b_id(line), &id_b) ||
                !string_to_uint(get_path_distance(line), &distance)) {
            return false;
        }
        if (!add_to_neighbours(id_a, id_b, distance, containers)) {
            return false;
        }
        line++;
    }
    return true;
}

bool add_to_neighbours(unsigned int id_a, unsigned int id_b, unsigned int distance, c_list_t *containers)
{
    container_t *container_a = c_get_by_id(containers, id_a);
    if (container_a == NULL) {
        return false;
    }
    container_t *container_b = c_get_by_id(containers, id_b);
    if (container_b == NULL) {
        return false;
    }
    if (cn_has_neighbor(container_a->neighbors, container_b->id)) {
        return true;
    }

    cn_node_t *new_neighbor = (cn_node_t *) create_n_node(container_a, distance);
    if (new_neighbor == NULL) {
        return false;
    }

    cn_node_t *new_neighbor2 = (cn_node_t *) create_n_node(container_b, distance);
    if (new_neighbor2 == NULL) {
        return false;
    }
    cn_list_insert(container_b->neighbors, new_neighbor);
    cn_list_insert(container_a->neighbors, new_neighbor2);
    return true;
}
