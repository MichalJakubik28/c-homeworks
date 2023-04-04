#ifndef PATHS_LOADING_H
#define PATHS_LOADING_H

#include "linked_list_utils.h"
bool load_paths(c_list_t *containers);
bool add_to_neighbours(unsigned int id_a, unsigned int id_b, unsigned int distance, c_list_t *containers);

#endif //PATHS_LOADING_H
