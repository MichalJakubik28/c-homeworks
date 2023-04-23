#include "persons.h"

#include "big_int.h"
#include "errors.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

static void swap(struct person *lhs, struct person *rhs)
{
    char *name = lhs->name;
    char *id = lhs->id;

    lhs->name = rhs->name;
    lhs->id = rhs->id;

    rhs->name = name;
    rhs->id = id;
}

static void ensort(struct persons *persons)
{
    struct person *current = persons->persons + persons->size - 1;
    for (; current != persons->persons; --current) {
        struct person *previous = current - 1;
        if (strcmp(previous->id, current->id) <= 0)
            break;
        swap(previous, current);
    }
}

static int person_cmp(const void *_id, const void *_person)
{
    const char *id = (const char *) _id;
    const struct person *person = (const struct person *) _person;
    return strcmp(id, person->id);
}

struct person *find_person(const struct persons *persons, const char *id)
{
    return (struct person *) bsearch(id, persons->persons, persons->size, sizeof(struct person), person_cmp);
}

static void destroy_persons(void *p)
{
    struct persons *persons = (struct persons *) p;

    for (int i = 0; i < persons->size; ++i) {
        free(persons->persons[i].id);
        free(persons->persons[i].name);
    }

    free(persons->persons);
}

void init_persons(struct persons *persons, int initial_capacity)
{
    object_avoid_duplicit_initialization(persons);
    persons->capacity = initial_capacity;
    persons->size = 0;
    OP(persons->persons = (struct person *) malloc(sizeof(struct person) * persons->capacity), ALLOCATION_FAILED);
    object_set_destructor(persons, destroy_persons);
}

void add_person(struct persons *persons, const char *id, const char *name)
{
    OP(!find_person(persons, id), PERSON_ALREADY_PRESENT);

    if (persons->capacity == persons->size) {
        persons->capacity *= 2;
        struct person *tmp;
        OP(tmp = (struct person *) realloc(persons->persons, persons->capacity * sizeof(struct person)), ALLOCATION_FAILED);
        persons->persons = tmp;
    }

    struct person *p = &persons->persons[persons->size];
    memset(p, 0, sizeof(*p));
    p->id = copy_string(id);
    p->name = copy_string(name);
    big_int_init(&p->amount);

    persons->size++;

    ensort(persons);
}
