#ifndef SITES_PROCESSING_H
#define SITES_PROCESSING_H

#include "linked_list_utils.h"

#include <stdbool.h>
s_list_t *assign_sites_to_containers(c_list_t *containers);
bool assign_neighbors_to_sites(c_list_t *containers);

#endif //SITES_PROCESSING_H
