#include "linked_list_utils.h"

#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>

void list_init(llist *list)
{
    assert(list != NULL);

    list->head = NULL;
    list->tail = NULL;
}

// appending containers
bool c_list_append(c_list_t *list, container_t *container)
{
    assert(list != NULL);
    assert(container != NULL);

    c_node_t *new_node = malloc(sizeof(c_node_t));

    if (new_node == NULL) {
        return false;
    }

    new_node->container = container;

    if (list->head == NULL) {
        list->head = new_node;
        new_node->prev = NULL;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }
    list->tail = new_node;
    new_node->next = NULL;

    return true;
}

// appending neighbors
bool n_list_append(llist *list, void *data, unsigned int distance)
{
    assert(list != NULL);
    assert(data != NULL);

    lln_node *new_node = malloc(sizeof(lln_node));

    if (new_node == NULL) {
        return false;
    }

    new_node->data = data;
    new_node->distance = distance;

    if (list->head == NULL) {
        list->head = new_node;
        new_node->prev = NULL;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }
    list->tail = new_node;
    new_node->next = NULL;

    return true;
}

// add new site node - need to add location as well
bool s_list_append(s_list_t *list, double x, double y)
{
    assert(list != NULL);

    s_node_t *new_node = malloc(sizeof(s_node_t));

    if (new_node == NULL) {
        return false;
    }

    new_node->x = x;
    new_node->y = y;
    new_node->neighbors = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        new_node->prev = NULL;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }
    list->tail = new_node;
    new_node->next = NULL;

    return true;
}

//bool c_list_append(c_list_t *list, container_t *container)
//{
//    assert(list != NULL);
//    assert(container != NULL);
//
//    c_node_t *new_node = malloc(sizeof(cn_node_t));
//
//    if (new_node == NULL) {
//        return false;
//    }
//
//    new_node->container = container;
//
//    if (list->head == NULL) {
//        list->head = new_node;
//        new_node->prev = NULL;
//    } else {
//        list->tail->next = new_node;
//        new_node->prev = list->tail;
//    }
//    list->tail = new_node;
//    new_node->next = NULL;
//
//    return true;
//}

bool n_list_push_front(cn_list_t  *list, container_t *container1, unsigned int distance)
{
    assert(list != NULL);
    assert(container1 != NULL);

    cn_node_t *new_node = malloc(sizeof(cn_node_t));

    if (new_node == NULL) {
        return false;
    }

    new_node->container = container1;
    new_node->distance = distance;

    if (list->head == NULL) {
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->head->prev = new_node;
        new_node->next = list->head;
    }
    new_node->prev = NULL;
    list->head = new_node;

    return true;
}


bool c_id_is_unique(c_list_t *list, unsigned int id)
{
    assert(list != NULL);

    c_node_t *node = list->head;

    while (node != NULL) {
        c_node_t *next = node->next;
        if (node->container->id == id) {
            return false;
        }
        node = next;
    }
    return true;
}

container_t *c_get_by_id(c_list_t *list, size_t id)
{
    assert(list != NULL);

    c_node_t *node = list->head;

    while (node != NULL) {
        c_node_t *next = node->next;
        if (node->container->id == id) {
            return node->container;
        }
        node = next;
    }

    return NULL;
}

bool cn_has_neighbor(cn_list_t  *list, size_t id)
{
    assert(list != NULL);

    cn_node_t *node = list->head;

    while (node != NULL) {
        cn_node_t *next = node->next;
        if (node->container->id == id) {
            return true;
        }
        node = next;
    }

    return false;
}

void destroy_containers(c_list_t *list)
{
    assert(list != NULL);

    c_node_t *curr_node = list->head;
    while (curr_node != NULL) {
        c_node_t *next_node = curr_node->next;
        if (curr_node->container != NULL) {
            free(curr_node->container->street);
            free(curr_node->container->name);
            destroy_neighbors((llist *) curr_node->container->neighbors);
            free(curr_node->container);
        }
        free(curr_node);
        curr_node = next_node;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}

void destroy_neighbors(llist *list)
{
    if (list == NULL) {
        return;
    }

    lln_node *curr_node = list->head;

    while (curr_node != NULL) {
        lln_node *next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}

void destroy_sites(s_list_t  *list)
{
    if (list == NULL) {
        return;
    }

    s_node_t *curr_node = list->head;

    while (curr_node != NULL) {
        s_node_t *next_node = curr_node->next;
        free(curr_node->waste_types);
        destroy_neighbors((llist *) curr_node->neighbors);
        free(curr_node);
        curr_node = next_node;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}

//bool n_list_append(cn_list_t  *list, container_t *container, unsigned int distance)
//{
//    assert(list != NULL);
//    assert(container != NULL);
//
//    cn_node_t *new_node = malloc(sizeof(cn_node_t));
//
//    if (new_node == NULL) {
//        return false;
//    }
//
//    new_node->container = container;
//    new_node->distance = distance;
//
//    if (list->head == NULL) {
//        list->head = new_node;
//        new_node->prev = NULL;
//    } else {
//        list->tail->next = new_node;
//        new_node->prev = list->tail;
//    }
//    list->tail = new_node;
//    new_node->next = NULL;
//
//    return true;
//}

bool cn_list_insert(cn_list_t *list, container_t *container1, unsigned int distance)
{
    assert(list != NULL);
    assert(container1 != NULL);

    cn_node_t *node = list->head;

    while (node != NULL) {
        cn_node_t *next = node->next;
        if (container1->id < node->container->id) {
            if (node == list->head) {
                return n_list_push_front(list, container1, distance);
            }

            // create node
            cn_node_t *new_node = malloc(sizeof(cn_node_t));
            if (new_node == NULL) {
                return false;
            }
            new_node->container = container1;
            new_node->distance = distance;

            // set pointers
            cn_node_t *prev = node->prev;
            new_node->next = node;
            new_node->prev = prev;
            node->prev = new_node;
            prev->next = new_node;
            return true;
        }
        node = next;
    }

    return n_list_append((llist *) list, container1, distance);
}

bool container_in_site(container_t *container1, s_node_t *site) {
    return fabs(container1->x - site->x) <= 0.00000000000001
            && fabs(container1->y - site->y) <= 0.00000000000001;
}

s_node_t *find_site(s_list_t *sites, container_t *container) {
    assert(sites != NULL);
    assert(container != NULL);

    s_node_t *node = sites->head;

    while (node != NULL) {
        s_node_t *next = node->next;

        if (container_in_site(container, node)) {
            return node;
        }

        node = next;
    }

    return NULL;
}
