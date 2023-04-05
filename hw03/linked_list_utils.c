#include "linked_list_utils.h"

#include <assert.h>
#include <limits.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>

void list_init(llist *list)
{
    assert(list != NULL);

    list->head = NULL;
    list->tail = NULL;
}

c_node_t *create_c_node(container_t *container)
{
    c_node_t *node = malloc(sizeof(c_node_t));

    if (node == NULL) {
        return NULL;
    }

    node->container = container;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

s_node_t *create_s_node(s_list_t *sites, double x, double y)
{
    assert(sites != NULL);

    s_node_t *node = malloc(sizeof(s_node_t));

    if (node == NULL) {
        return NULL;
    }

    site_t *new_site = malloc(sizeof(site_t));

    if (new_site == NULL) {
        free(node);
        return NULL;
    }

    new_site->predecessor = NULL;
    new_site->shortest_distance = UINT_MAX;

    sn_list_t *site_neighbors = malloc(sizeof(sn_list_t));
    if (site_neighbors == NULL) {
        free(node);
        free(new_site);
        return NULL;
    }
    list_init((llist *) site_neighbors);

    node->site = new_site;

    node->site->x = x;
    node->site->y = y;
    node->site->id = sites->tail == NULL ? 1 : sites->tail->site->id + 1;
    node->site->neighbors = site_neighbors;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

lln_node *create_n_node(void *data, unsigned int distance)
{
    assert(data != NULL);

    lln_node *node = malloc(sizeof(lln_node));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->distance = distance;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// appending containers
void list_append(llist *list, ll_node *node)
{
    assert(list != NULL);
    assert(node != NULL);

    if (list->head == NULL) {
        list->head = (lln_node *) node;
        node->prev = NULL;
    } else {
        list->tail->next = (lln_node *) node;
        node->prev = (ll_node *) list->tail;
    }
    list->tail = (lln_node *) node;
    node->next = NULL;
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

// add new site node - node with site struct in it
bool s_list_append(s_list_t *list, double x, double y)
{
    assert(list != NULL);

    s_node_t *new_node = malloc(sizeof(s_node_t));
    if (new_node == NULL) {
        return false;
    }

    site_t *site = malloc(sizeof(site_t));
    if (site == NULL) {
        free(new_node);
        return NULL;
    }

    new_node->site = site;
    new_node->site->x = x;
    new_node->site->y = y;
    new_node->site->neighbors = NULL;

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

void list_push_front(llist *list, lln_node *node)
{
    assert(list != NULL);
    assert(node != NULL);

    if (list->head == NULL) {
        node->next = NULL;
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
    }
    node->prev = NULL;
    list->head = node;
}

bool n_list_push_front(cn_list_t *list, container_t *container1, unsigned int distance)
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

site_t *sn_get_by_id(sn_list_t *list, size_t id)
{
    assert(list != NULL);

    sn_node_t *node = list->head;

    while (node != NULL) {
        sn_node_t *next = node->next;
        if (node->site->id == id) {
            return node->site;
        }
        node = next;
    }

    return NULL;
}

s_node_t *s_get_by_id(s_list_t *list, size_t id)
{
    assert(list != NULL);

    s_node_t *node = list->head;

    while (node != NULL) {
        s_node_t *next = node->next;
        if (node->site->id == id) {
            return node;
        }
        node = next;
    }

    return NULL;
}

s_node_t *s_get_by_site(s_list_t *list, site_t *site)
{
    assert(list != NULL);

    s_node_t *node = list->head;

    while (node != NULL) {
        s_node_t *next = node->next;
        if (node->site == site) {
            return node;
        }
        node = next;
    }

    return NULL;
}

bool cn_has_neighbor(cn_list_t *list, size_t id)
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

void destroy_sites(s_list_t *list)
{
    if (list == NULL) {
        return;
    }

    s_node_t *curr_node = list->head;

    while (curr_node != NULL) {
        s_node_t *next_node = curr_node->next;
        free(curr_node->site->waste_types);
        destroy_neighbors((llist *) curr_node->site->neighbors);
        free(curr_node->site);
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

//void list_insert(llist *list, lln_node *node) {
//    assert(list != NULL);
//    assert(node != NULL);
//
//    lln_node *curr_node = list->head;
//
//    while (curr_node != NULL) {
//        lln_node *next = curr_node->next;
//        if (node->data->id < () curr_node->data {
//            if (curr_node == list->head) {
//                return list_push_front(list, node);
//            }
//
//            // set pointers
//            cn_node_t *prev = curr_node->prev;
//            new_node->next = curr_node;
//            new_node->prev = prev;
//            curr_node->prev = new_node;
//            prev->next = new_node;
//            return;
//        }
//        curr_node = next;
//    }
//    list_append((llist *) list, (ll_node *) node);
//}

void cn_list_insert(cn_list_t *list, cn_node_t *node)
{
    assert(list != NULL);
    assert(node != NULL);

    cn_node_t *curr_node = list->head;

    while (curr_node != NULL) {
        cn_node_t *next = curr_node->next;
        if (node->container->id < curr_node->container->id) {
            if (curr_node == list->head) {
                list_push_front((llist *) list, (lln_node *) node);
                return;
            }

            // set pointers
            cn_node_t *prev = curr_node->prev;
            node->next = curr_node;
            node->prev = prev;
            curr_node->prev = node;
            prev->next = node;
            return;
        }
        curr_node = next;
    }
    list_append((llist *) list, (ll_node *) node);
}

void sn_list_insert(sn_list_t *list, sn_node_t *node)
{
    assert(list != NULL);
    assert(node != NULL);

    sn_node_t *curr_node = list->head;

    while (curr_node != NULL) {
        sn_node_t *next = curr_node->next;
        if (node->site->id < curr_node->site->id) {
            if (curr_node == list->head) {
                list_push_front((llist *) list, (lln_node *) node);
                return;
            }

            // set pointers
            sn_node_t *prev = curr_node->prev;
            node->next = curr_node;
            node->prev = prev;
            curr_node->prev = node;
            prev->next = node;
            return;
        }
        curr_node = next;
    }
    list_append((llist *) list, (ll_node *) node);
}

bool container_in_site(container_t *container1, s_node_t *site_node)
{
    return fabs(container1->x - site_node->site->x) <= 0.00000000000001 && fabs(container1->y - site_node->site->y) <= 0.00000000000001;
}

s_node_t *find_site(s_list_t *sites, container_t *container)
{
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

void remove_from_list(s_list_t *list, s_node_t *node_to_remove)
{
    if (node_to_remove == list->head) {
        list->head = node_to_remove->next;
        if (node_to_remove->next != NULL) {
            node_to_remove->next->prev = NULL;
        } else {
            list->tail = NULL;
        }

    } else if (node_to_remove == list->tail) {
        if (node_to_remove->prev != NULL) {
            node_to_remove->prev->next = NULL;
            list->tail = node_to_remove->prev;
        } else {
            list->head = NULL;
            list->tail = NULL;
        }
    } else {
        s_node_t *prev = node_to_remove->prev;
        s_node_t *next = node_to_remove->next;
        prev->next = next;
        next->prev = prev;
    }

    node_to_remove->next = NULL;
    node_to_remove->prev = NULL;
}

void s_list_insert_by_distance(s_list_t *list, s_node_t *node)
{
    assert(list != NULL);
    assert(node != NULL);

    s_node_t *curr_node = list->head;

    while (curr_node != NULL) {
        s_node_t *next = curr_node->next;
        if (node->site->shortest_distance < curr_node->site->shortest_distance) {
            if (curr_node == list->head) {
                list_push_front((llist *) list, (lln_node *) node);
                return;
            }

            // set pointers
            s_node_t *prev = curr_node->prev;
            node->next = curr_node;
            node->prev = prev;
            curr_node->prev = node;
            prev->next = node;
            return;
        }
        curr_node = next;
    }
    list_append((llist *) list, (ll_node *) node);
}
