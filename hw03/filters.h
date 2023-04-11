#include "linked_list_utils.h"

#include <stdbool.h>
#ifndef HW03_FILTERS_H
#define HW03_FILTERS_H

/**
 * @brief Applies waste type filter on a container if it's used.
 *
 * @param container1 container that the filter should be applied to
 * @param filter_used whether the filter should be applied
 * @param waste_types array of waste types
 *
 * @retval true if container passes the filtering criteria, else false
 */
bool filter_waste_type(container_t *container1, bool filter_used, char waste_types[7]);

/**
 * @brief Applies capacity filter on a container if it's used.
 *
 * @param container1 container that the filter should be applied to
 * @param filter_used whether the filter should be applied
 * @param capacity array of capacity limits ( [min, max] )
 *
 * @retval true if container passes the filtering criteria, else false
 */
bool filter_capacity(container_t *container1, bool filter_used, const unsigned int capacity[2]);

/**
 * @brief Applies accessibility  filter on a container if it's used.
 *
 * @param container1 container that the filter should be applied to
 * @param filter_used whether the filter should be applied
 * @param public accessibility flag
 *
 * @retval true if container passes the filtering criteria, else false
 */
bool filter_accessibility(container_t *container1, bool filter_used, bool public);

#endif //HW03_FILTERS_H
