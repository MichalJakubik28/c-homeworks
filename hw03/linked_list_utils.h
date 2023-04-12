#ifndef LINKED_LIST_UTILS_H
#define LINKED_LIST_UTILS_H

#include "container_loading.h"

#include <stdbool.h>
#include <stddef.h>

struct site_neighbor_node
{
    sn_node_t *prev;
    sn_node_t *next;
    site_t *site;
    unsigned int distance;
};

struct site_neighbor_list
{
    sn_node_t *head;
    sn_node_t *tail;
};

struct site_node
{
    s_node_t *prev;
    s_node_t *next;
    site_t *site;
};

struct site_list
{
    s_node_t *head;
    s_node_t *tail;
};

struct container_neighbor_node
{
    cn_node_t *prev;
    cn_node_t *next;
    container_t *container;
    unsigned int distance;
};

struct container_neighbor_list
{
    cn_node_t *head;
    cn_node_t *tail;
};

struct container_node
{
    c_node_t *prev;
    c_node_t *next;
    container_t *container;
};

struct container_list
{
    c_node_t *head;
    c_node_t *tail;
};

// generic structures for list manipulation

struct linked_list_node
{
    ll_node *prev;
    ll_node *next;
    void *data;
};

struct linked_list
{
    lln_node *head;
    lln_node *tail;
};

struct linked_list_neighbor_node
{
    lln_node *prev;
    lln_node *next;
    void *data;
    unsigned int distance;
};

// site representation
struct site
{
    unsigned int id;
    double x;
    double y;
    char *waste_types;
    sn_list_t *neighbors;
    site_t *predecessor;
    unsigned int shortest_distance;
};

// container representation
struct container
{
    unsigned int id;
    double x, y;
    char waste_type;
    unsigned int capacity;
    char *name;
    char *street;
    unsigned int number;
    bool public;
    cn_list_t *neighbors;
    site_t *site;
};

// functions that I managed to implement generically for all structs

/**
 * @brief Initializes linked list.
 *
 * @param list linked list to initialize
 */
void list_init(llist *list);

/**
 * @brief Appends a node to the end of the list.
 *
 * @param list linked list instance
 * @param node node to append to the linked list
 */
void list_append(llist *list, ll_node *node);

/**
 * @brief Removes node from a linked list.
 *
 * @param list linked list instance
 * @param node node to be removed from the linked list
 */
void remove_from_list(s_list_t *list, s_node_t *node_to_remove);

// functions that could not be united because they work with specific structures

/**
 * @brief Creates a container node.
 *
 * @param container container to create a node from
 * @retval container linked list node
 */
c_node_t *create_c_node(container_t *container);

/**
 * @brief Creates a site and its node.
 *
 * @param sites list of sites
 * @param x x coordinate of the site
 * @param y y coordinate of the site
 * @retval site linked list node
 */
s_node_t *create_s_node(s_list_t *sites, double x, double y);

/**
 * @brief Creates a neighbor node.
 *
 * @param data data of the neighbor
 * @param distance distance to the neighbor
 * @retval neighbor linked list node
 */
lln_node *create_n_node(void *data, unsigned int distance);

/**
 * @brief Destroys containers linked list.
 *
 * @param list containers to destroy
 */
void destroy_containers(c_list_t *list);

/**
 * @brief Destroys neighbors linked list.
 *
 * @param list neighbors to destroy
 */
void destroy_neighbors(llist *list);

/**
 * @brief Destroys sites linked list.
 *
 * @param list sites to destroy
 */
void destroy_sites(s_list_t *list);

/**
 * @brief Gets container from list by its ID.
 *
 * @param list containers
 * @param id id of the target container
 *
 * @retval container instance with given ID or NULL if not found
 */
container_t *c_get_by_id(c_list_t *list, size_t id);

/**
 * @brief Gets site neighbor from list by its ID.
 *
 * @param list sites
 * @param id id of the target site neighbor
 *
 * @retval site instance with given ID or NULL if not found
 */
site_t *sn_get_by_id(sn_list_t *list, size_t id);

/**
 * @brief Finds site of the container.
 *
 * @param sites sites linked list
 * @param container container which site is to be found
 *
 * @retval site instance with given ID or NULL if not found
 */
s_node_t *find_site(s_list_t *sites, container_t *container);

/**
 * @brief Gets site node from list by its site.
 *
 * @param list sites
 * @param site site of the target node
 *
 * @retval site node of given site or NULL if not found
 */
s_node_t *s_get_by_site(s_list_t *list, site_t *site);

/**
 * @brief Gets site from list by its ID.
 *
 * @param list containers
 * @param id id of the target site
 *
 * @retval site instance with given ID or NULL if not found
 */
s_node_t *s_get_by_id(s_list_t *list, size_t id);

/**
 * @brief Checks if container neighbor already has a neighbor with given ID
 *
 * @param list container neighbors
 * @param id id of the target container
 *
 * @retval true if such container is found, else false
 */
bool cn_has_neighbor(cn_list_t *list, size_t id);

/**
 * @brief Inserts container neighbor node into linked list by ID
 *
 * @param list container neighbors
 * @param node node to be inserted
 *
 */
void cn_list_insert(cn_list_t *list, cn_node_t *node);

/**
 * @brief Inserts site neighbor node into linked list by ID
 *
 * @param list site neighbors
 * @param node node to be inserted
 *
 */
void sn_list_insert(sn_list_t *list, sn_node_t *node);

/**
 * @brief Inserts site node into linked list by distance
 *
 * @param list sites
 * @param node node to be inserted
 *
 */
void s_list_insert_by_distance(s_list_t *list, s_node_t *node);

#endif //LINKED_LIST_UTILS_H
