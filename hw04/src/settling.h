#ifndef SETTLING_H
#define SETTLING_H

#include "currency.h"
#include "persons.h"

void settle_debt(struct persons *persons, struct currency_table *table);
void settle_effectively(struct persons *persons, struct currency_table *table);
struct person *find_extreme(struct persons *persons, int sign);
void generate_combinations(int subset_size, const int *persons_count, int result[], int curr_number, int curr_index, int curr_combination[], int *array_index);
int combinations_count(int n, int k);

#endif //SETTLING_H
