#ifndef PATHS_LOADING_H
#define PATHS_LOADING_H

#include "linked_list_utils.h"

/**
 * @brief Loads info about all paths from data source into a linked list.
 *
 * @retval linked list of paths
 */
bool load_paths(c_list_t *containers);

/**
 * @brief Interlinks containers based on a path between them.
 *
 * @param id_a ID of the first container
 * @param id_b ID of the second container
 * @param distance distance between the two containers
 * @param containers linked list of containers
 *
 * @retval true if such containers exist and could be successfully interlinked, else false
 */
bool add_to_neighbours(unsigned int id_a, unsigned int id_b, unsigned int distance, c_list_t *containers);

#endif //PATHS_LOADING_H
