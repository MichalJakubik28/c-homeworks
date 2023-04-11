#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <stdbool.h>

typedef struct site_neighbor_node sn_node_t;
typedef struct site_neighbor_list sn_list_t;

typedef struct site_node s_node_t;
typedef struct site_list s_list_t;

typedef struct container_neighbor_node cn_node_t;
typedef struct container_node c_node_t;

typedef struct container_neighbor_list cn_list_t;
typedef struct container_list c_list_t;

typedef struct container container_t;
typedef struct site site_t;

// generic structures to unify linked list operations for types of linked lists above
typedef struct linked_list llist;
typedef struct linked_list_neighbor_node lln_node;
typedef struct linked_list_node ll_node;

/**
 * @brief Loads info about all containers from data source into a linked list.
 *
 * @retval linked list of containers
 */
c_list_t *load_containers(void);

#endif //DATA_HANDLING_H
