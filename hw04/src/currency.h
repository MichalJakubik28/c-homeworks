#include "errors.h"
#include "utils.h"

#ifndef CURRENCY_H
#define CURRENCY_H

struct currency
{
    char *name;
    long rating;
};

struct currency_table
{
    struct object _object;
    struct currency *currencies;
    char *main_currency;
    int size;
    int capacity;
};

void init_currency_table(struct currency_table *table);
void add_currency(struct currency_table *table, const char *name, long rating);
long convert_currency(struct currency_table *table, long amount, const char *currency);

#endif
