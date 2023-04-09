#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "linked_list_utils.h"

#define INVALID_TARGET (-1)
#define NO_PATH 0
#define PATH_FOUND 1

bool dijkstra(s_list_t *sites, unsigned int start_id, unsigned int target_id, site_t **target_site);
unsigned int path_length(site_t *site);

#endif //DIJKSTRA_H
