#ifndef SITES_PROCESSING_H
#define SITES_PROCESSING_H

#include "linked_list_utils.h"

#include <stdbool.h>

/**
 * @brief Assigns a site to every container. If a suitable site does not exist, creates a new one.
 *
 * @param containers containers linked list
 * @retval linked list of sites
 */
s_list_t *assign_sites_to_containers(c_list_t *containers);

/**
 * @brief Assigns neighboring sites to each site in the list using the neighbors of the containers forming the site.
 *
 * @param containers containers linked list
 * @retval linked list of containers
 */
bool assign_neighbors_to_sites(c_list_t *containers);

#endif //SITES_PROCESSING_H
