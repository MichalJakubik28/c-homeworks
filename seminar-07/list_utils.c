#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "list_utils.h"

//-----------------------------------------------------------------------------
//  Convenience macros
//-----------------------------------------------------------------------------

// --<----<----<----<----<----<----<----<----<----<----<----<----<----<----<--
// REMOVE THESE MACROS WHEN DONE
// --<----<----<----<----<----<----<----<----<----<----<----<----<----<----<--

// See ⟨list.c⟩ for explanation on what these macros do.

#define UNUSED(VARIABLE)                                                    \
    ((void) (VARIABLE))

#define NOT_IMPLEMENTED()                                                   \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        abort();                                                            \
    } while (0)

//-----------------------------------------------------------------------------
//  Implementation
//-----------------------------------------------------------------------------

bool list_any(const struct list *list, predicate p)
{
    /* TODO: Do not forget to add ⟨assert()⟩ checks to other functions. */
    assert(list != NULL);
    assert(p != NULL);

    if (list->head == NULL) {
        return false;
    }

    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (p(node->data)) {
            return true;
        }
        node = next;
    }

    return false;
}

bool list_all(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    if (list->head == NULL) {
        return true;
    }

    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (!p(node->data)) {
            return false;
        }
        node = next;
    }

    return true;
}

bool list_insert(struct list *list, size_t index, void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    size_t curr_index = 0;
    struct node *node = list->head;

    if (index == 0) {
        return list_push_front(list, data);
    }

    while (node != NULL) {
        struct node *next = node->next;
        if (curr_index == index) {

            // create node
            struct node *new_node = malloc(sizeof(struct node));
            if (new_node == NULL) {
                return false;
            }
            void *new_data = malloc(list->elem_size);
            if (data == NULL) {
                return false;
            }
            memcpy(new_data, data, list->elem_size);
            new_node->data = new_data;

            // set pointers
            struct node *prev = node->prev;
            new_node->next = node;
            new_node->prev = prev;
            node->prev = new_node;
            prev->next = new_node;
            return true;
        }
        node = next;
        curr_index++;
    }

    return list_push_back(list, data);
}

const void *list_get(const struct list *list, size_t index)
{
    assert(list != NULL);

    size_t curr_index = 0;
    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (curr_index == index) {
            return node->data;
        }
        node = next;
        curr_index++;
    }

    return NULL;
}

int list_get_index(const struct list *list, const void *data)
{
    assert(list != NULL);

    int curr_index = 0;
    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (memcmp(data, node->data, list->elem_size) == 0) {
            return curr_index;
        }
        node = next;
        curr_index++;
    }

    return -1;
}

bool list_remove(struct list *list, size_t index, void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    size_t curr_index = 0;
    struct node *node = list->head;

    if (index == 0) {
        return list_pop_front(list, data);
    }

    while (node != NULL && node != list->tail) {
        struct node *next = node->next;
        if (curr_index == index) {

            if (data != NULL) {
                memcpy(data, node->data, list->elem_size);
            }

            // set pointers
            struct node *prev = node->prev;
            next->prev = prev;
            prev->next = next;
            free(node);
            return true;
        }
        node = next;
        curr_index++;
    }

    return list_pop_back(list, data);
}

const void* list_find_first(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    if (list->head == NULL) {
        return NULL;
    }

    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (p(node->data)) {
            return node->data;
        }
        node = next;
    }

    return NULL;
}

const void* list_find_last(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    if (list->tail == NULL) {
        return NULL;
    }

    struct node *node = list->tail;

    while (node != NULL) {
        struct node *prev = node->prev;
        if (p(node->data)) {
            return node->data;
        }
        node = prev;
    }

    return NULL;
}

void list_for_each(struct list *list, action f, void *context)
{
    assert(list != NULL);
    assert(context != NULL);

    if (list->head == NULL) {
        return;
    }

    struct node *node = list->head;

    while (node != NULL) {
        struct node *next = node->next;
        if (f(node->data, context) != ACTION_CONTINUE) {
            return;
        }
        node = next;
    }
}

void list_for_each_reverse(struct list *list, action f, void *context)
{
    assert(list != NULL);
    assert(context != NULL);

    if (list->tail == NULL) {
        return;
    }

    struct node *node = list->tail;

    while (node != NULL) {
        struct node *prev = node->prev;
        if (f(node->data, context) != ACTION_CONTINUE) {
            return;
        }
        node = prev;
    }
}

void list_sort(struct list *list, comparator cmp)
{
    assert(list != NULL);
    assert(cmp != NULL);

    size_t swapped = 0;
    do {
        swapped = 0;
        struct node *node = list->head;
        while (node->next != NULL) {
            struct node *next = node->next;
            if (cmp(node->data, next->data) > 0) {
                if (node == list->head) {
                    list->head = next;
                }
                if (next == list->tail) {
                    list->tail = node;
                }
                next->prev = node->prev;
                node->next = next->next;
                if (node->prev != NULL) {
                    node->prev->next = next;
                }
                node->prev = next;
                if (next->next != NULL) {
                    next->next->prev = node;
                }
                next->next = node;

                swapped++;
            }
            node = next;
        }
    }
    while (swapped != 0);
}
