#ifndef SITES_PROCESSING_H
#define SITES_PROCESSING_H

#include "linked_list_utils.h"

#include <stdbool.h>
s_list_t *assign_sites_to_containers(c_list_t *containers);
bool assign_neighbors_to_sites(c_list_t *containers);
site_t *s_get_by_id(s_list_t *list, size_t id);

#endif //SITES_PROCESSING_H
