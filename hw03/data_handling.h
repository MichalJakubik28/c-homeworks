#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <stdbool.h>
typedef struct container_t {
    unsigned int id;
    double x, y;
    char trash_type;
    unsigned int capacity;
    char *name;
    char *street;
    unsigned int number;
    bool public;
} container_t;

container_t** load_and_validate(void);
void testZasobnik(void);

#endif //DATA_HANDLING_H
