#include "filters.h"

#include <assert.h>
#include <string.h>

bool filter_waste_type(container_t *container1, bool filter_used, char waste_types[7])
{
    assert(container1 != NULL);
    return !filter_used || strchr(waste_types, container1->waste_type) != NULL;
}

bool filter_capacity(container_t *container1, bool filter_used, const unsigned int capacity[2])
{
    assert(container1 != NULL);
    return !filter_used || (container1->capacity >= capacity[0] && container1->capacity <= capacity[1]);
}

bool filter_accessibility(container_t *container1, bool filter_used, bool public)
{
    return !filter_used || container1->public == public;
}
