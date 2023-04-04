#include "sites_processing.h"

#include "input_handling.h"

#include <assert.h>
#include <malloc.h>

s_list_t *assign_sites_to_containers(c_list_t *containers) {
    s_list_t *sites_list = malloc(sizeof(s_list_t));
    if (sites_list == NULL) {
        return NULL;
    }
    list_init((llist *) sites_list);

    c_node_t *node = containers->head;

    while (node != NULL) {
        c_node_t *next = node->next;

        // find suitable site_node
        s_node_t *site_node = find_site(sites_list, node->container);

        // no suitable site found
        if (site_node == NULL) {

            // create new site
            site_node = create_s_node(sites_list, node->container->x, node->container->y);
            if (site_node == NULL) {
                destroy_sites(sites_list);
                return NULL;
            }

            list_append((llist *) sites_list, (ll_node *) site_node);

            // attach site to the container
            node->container->site = site_node->site;

            // initialize site's waste types
            char *waste_types = calloc(7, sizeof(char));
            if (waste_types == NULL) {
                destroy_sites(sites_list);
                return NULL;
            }
            site_node->site->waste_types = waste_types;
        } else {
            node->container->site = site_node->site;
        }

        // add container's waste type to site's waste types
        add_to_types(node->container->waste_type, site_node->site->waste_types);

        node = next;
    }
    return sites_list;
}

bool neighbor_container_sites(container_t *container) {
    assert(container != NULL);

    cn_node_t *container_neighbor = container->neighbors->head;

    while (container_neighbor != NULL) {
        cn_node_t *next = container_neighbor->next;

        sn_node_t *new_neighbor = (sn_node_t *) create_n_node(container_neighbor->container->site, container_neighbor->distance);
        if (new_neighbor == NULL) {
            free(new_neighbor);
            return false;
        }
        if (sn_get_by_id(container->site->neighbors, new_neighbor->site->id) == NULL) {
            sn_list_insert(container->site->neighbors, new_neighbor);
        } else {
            free(new_neighbor);
        }

        container_neighbor = next;
    }

    return true;
}

bool assign_neighbors_to_sites(c_list_t *containers) {
    assert(containers != NULL);

    c_node_t *container_node = containers->head;

    while (container_node != NULL) {
        c_node_t *next = container_node->next;

        if (!neighbor_container_sites(container_node->container)) {
            return false;
        }

        container_node = next;
    }

    return true;
}

