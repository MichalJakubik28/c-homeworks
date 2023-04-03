#include "sites_processing.h"

#include "input_handling.h"

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

        // find suitable site
        s_node_t *site = find_site(sites_list, node->container);
        if (site == NULL) {
            s_list_append(sites_list, node->container->x, node->container->y);
            site = sites_list->tail;
            node->container->site = site;
            char *waste_types = calloc(7, sizeof(char));
            if (waste_types == NULL) {
                destroy_sites(sites_list);
                return NULL;
            }
            site->waste_types = waste_types;
        } else {
            node->container->site = site;
        }

        add_to_types(node->container->waste_type, site->waste_types);
        node = next;
    }
    return sites_list;
}
