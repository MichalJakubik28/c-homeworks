#include "data_handling.h"

#include "data_source.h"
#include "input_handling.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct zasobnik
{
    int hodnota;
    struct zasobnik *naslednik;
} typZasobnik;

void push(typZasobnik **z, int hodnota) {
    typZasobnik *pom = (typZasobnik*) malloc(sizeof(typZasobnik));
    pom->hodnota = hodnota;
    pom->naslednik = *z;
    *z = pom;
}

void testZasobnik(void) {
    typZasobnik zasobnik;
    zasobnik.naslednik = NULL;
    zasobnik.hodnota = 13;
    typZasobnik *pZasobnik = &zasobnik;
    push(&pZasobnik, 5);
    printf("%d, naslednik %p", pZasobnik->hodnota, (void*) pZasobnik->naslednik);
}

bool parse_container_id(const char *id, container_t *container) {
    char *unparsed;
    unsigned long long_id= strtol(id, &unparsed, 10);
    if (unparsed[0] != 0 || long_id >= UINT_MAX) {
        return false;
    }
    container->id = long_id;
    return true;
}

bool parse_container_x(const char *x, container_t *container) {
    char *unparsed;
    double double_x = strtod(x, &unparsed);
    if (unparsed[0] != 0) {
        return false;
    }
    container->x = double_x;
    return true;
}

bool parse_container_y(const char *y, container_t *container) {
    char *unparsed;
    double double_y = strtod(y, &unparsed);
    if (unparsed[0] != 0) {
        return false;
    }
    container->y = double_y;
    return true;
}

bool parse_container_waste(const char *type, container_t *container) {
    if (strcmp(type, "Plastics and Aluminium") == 0) {
        container->trash_type = plastics_aluminium;
        return true;
    }
    if (strcmp(type, "Paper") == 0) {
        container->trash_type = paper;
        return true;
    }
    if (strcmp(type, "Biodegradable waste") == 0) {
        container->trash_type = biodegradable_waste;
        return true;
    }
    if (strcmp(type, "Clear glass") == 0) {
        container->trash_type = clear_glass;
        return true;
    }
    if (strcmp(type, "Colored glass") == 0) {
        container->trash_type = clear_glass;
        return true;
    }
    if (strcmp(type, "Textile") == 0) {
        container->trash_type = textile;
        return true;
    }
    return false;
}

bool parse_container_capacity(const char *capacity, container_t *container) {
    char *unparsed;
    unsigned long long_capacity= strtol(capacity, &unparsed, 10);
    if (unparsed[0] != 0 || long_capacity >= UINT_MAX) {
        return false;
    }
    container->capacity = long_capacity;
    return true;
}

bool parse_container_name(const char *name, container_t *container) {
    size_t length = strlen(name);
    char container_name[length + 1];
    memset(container_name, 0, length + 1);
    strcpy(container_name, name);
    container->name = container_name;
    return true;
}

bool parse_container_address(const char *address, container_t *container) {
    size_t length = strlen(address);
    char container_address[length + 1];
    memset(container_address, 0, length + 1);
    strcpy(container_address, address);
    container->street = container_address;
    return true;
}

bool parse_container_number(const char *number, container_t *container) {
    if (strlen(number) == 0) {
        container->number = UINT_MAX;
        return true;
    }
    char *unparsed;
    unsigned long long_number= strtol(number, &unparsed, 10);
    if (unparsed[0] != 0 || long_number >= UINT_MAX) {
        return false;
    }
    container->number = long_number;
    return true;
}

bool parse_container_public(const char *public, container_t *container) {
    if (strlen(public) != 1) {
        return false;
    }

    switch (public[0]) {
    case 'Y':
        container->public = true;
        return true;
    case 'N':
        container->public = false;
        return true;
    default:
        return false;
    }
}

container_t* create_container(size_t line) {
    container_t *p_container = malloc(sizeof(container_t));

    if (p_container == NULL) {
            return NULL;
    }

    const char * (*get_param[]) (size_t) = {
        &get_container_id,
        &get_container_x,
        &get_container_y,
        &get_container_waste_type,
        &get_container_capacity,
        &get_container_name,
        &get_container_street,
        &get_container_number,
        &get_container_public};
    bool (*parse_param[]) (const char *, container_t *) = {
        &parse_container_id,
        &parse_container_x,
        &parse_container_y,
        &parse_container_waste,
        &parse_container_capacity,
        &parse_container_name,
        &parse_container_address,
        &parse_container_number,
        &parse_container_public};

    for (int i = 0; i < 9; i++) {
            if (!parse_param[i](get_param[i](line), p_container)) {
                fprintf(stderr, "Could not parse argument no. %d\n", i);
                free(p_container);
                return NULL;
            }
    }

    return p_container;
}

/*

ID kontejneru (unikátní pro každý kontejner, nezáporné celé číslo, maximálně UINT_MAX - 1)

Zeměpisná šířka (číslo s přesností až 15 desetinných míst, pro uložení bude stačit typ double)

Zeměpisná délka (číslo s přesností až 15 desetinných míst, pro uložení bude stačit typ double)

Typ tříděného odpadu, který je jedním z následujících:

    Plastics and Aluminium
    Paper
    Biodegradable waste
    Clear glass
    Colored glass
    Textile

Kapacita kontejneru v litrech (nezáporné celé číslo, maximálně UINT_MAX - 1)

Název kontejneru (nepovinné)

Ulice (nepovinné)

Číslo popisné (nezáporné celé číslo, maximálně UINT_MAX - 1, nepovinné)

Informace o tom, zda je kontejner veřejně přístupný (obsahuje pouze hodnoty Y nebo N)

*/


void free_container_array(container_t *array[], unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
            free(array[i]);
    }
    free(array);
}

container_t** load_and_validate(void) {
    unsigned int line = 0;
    unsigned int alloc_size = 64;
    //  memset?
    container_t **containers = calloc(sizeof(container_t), alloc_size);
    if (containers == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
    }
    while (get_container_id(line) != NULL) {
        container_t *container = create_container(line);

        if (container == NULL) {
            free_container_array(containers, line);
            return NULL;
        }

        if (line == alloc_size - 1) {
            alloc_size = alloc_size << 1;
            container_t **longer_containers = realloc(containers, alloc_size * sizeof(container_t));
            if (longer_containers == NULL) {
                fprintf(stderr, "Could not reallocate memory\n");
                free_container_array(containers, line);
                return NULL;
            }
            containers = longer_containers;
            memset(containers + (alloc_size >> 1), 0, (alloc_size >> 1));
        }

        containers[line] = container;
        line++;
    }
    for (size_t i = 0; i < line; i++) {
        printf("Container no. %lu: ID: %u, Type: %hd, Capacity: %u, Address: %s %u\n", i, containers[i]->id, containers[i]->trash_type, containers[i]->capacity, containers[i]->street, containers[i]->number);
    }
    printf("%d entries in total\n", line);
    return containers;
}




