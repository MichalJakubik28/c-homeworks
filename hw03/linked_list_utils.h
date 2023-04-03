#ifndef HW03_LINKED_LIST_UTILS_H
#define HW03_LINKED_LIST_UTILS_H

#include "container_loading.h"

#include <stdbool.h>
#include <stddef.h>

struct site_neighbor_node {
    sn_node_t *prev;
    sn_node_t *next;
    s_node_t *site;
    unsigned int distance;
};

struct site_neighbor_list {
    sn_node_t *head;
    sn_node_t *tail;
};

struct site_node {
    s_node_t *next;
    s_node_t *prev;
    double x;
    double y;
    char *waste_types;
    s_list_t *neighbors;
};

struct site_list {
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

struct linked_list_node {
    ll_node *prev;
    ll_node *next;
    void *data;
};

struct linked_list {
    lln_node *head;
    lln_node *tail;
};

struct linked_list_neighbor_node {
    lln_node *prev;
    lln_node *next;
    void *data;
    unsigned int distance;
};

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
    s_node_t *site;
};

//void c_list_init(c_list_t *list);
void list_init(llist *list);
bool c_list_append(c_list_t *list, container_t *container);
bool n_list_append(llist *list, void *data, unsigned int distance);
bool s_list_append(s_list_t *list, double x, double y);
void destroy_containers(c_list_t *list);
void destroy_neighbors(llist *list);
void destroy_sites(s_list_t  *list);
bool c_id_is_unique(c_list_t *list, unsigned int id);
container_t *c_get_by_id(c_list_t *list, size_t id);
//void cn_list_init(cn_list_t *list);
//bool cn_list_append(cn_list_t *list, container_t *container, unsigned int distance);
bool cn_has_neighbor(cn_list_t *list, size_t id);
bool cn_list_insert(cn_list_t *list, container_t *container1, unsigned int distance);
s_node_t *find_site(s_list_t *sites, container_t *container);

#endif //HW03_LINKED_LIST_UTILS_H
