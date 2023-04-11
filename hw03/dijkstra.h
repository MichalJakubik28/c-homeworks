#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "linked_list_utils.h"

/**
 * @brief Runs Dijkstra's algorithm for finding the shortest path in an oriented graph adapted for searching container sites.
 *
 * @param sites sites list to be searched
 * @param start_id ID of the starting site
 * @param target_id ID of the target site
 * @param target_site pointer to a place where a pointer to the found target should be saved
 *
 * @retval true if finding path ended without errors (does not imply path existence), else false
 */
bool dijkstra(s_list_t *sites, unsigned int start_id, unsigned int target_id, site_t **target_site);

/**
 * @brief Counts the path length between two sites after running Dijkstra.
 *
 * @param site target site instance
 */
unsigned int path_length(site_t *site);

#endif //DIJKSTRA_H
