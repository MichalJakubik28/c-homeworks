#ifndef SETTLING_H
#define SETTLING_H

#include "currency.h"
#include "persons.h"

/**
 * @brief Settles debts between persons.
 *
 * @param persons persons to settle debts between
 * @param table currency table
 */
void settle_debt(struct persons *persons, struct currency_table *table);

/**
 * @brief Settles debts between persons in the least possible money transfers.
 *
 * @param persons persons to settle debts between
 * @param table currency table
 */
void settle_effectively(struct persons *persons, struct currency_table *table);

/**
* @brief Finds a person with the most debt/credit.
*
* @param persons persons to settle debts between
* @param sign indicating whether the most indebted
* person is sought (negative number) or the most credited one (positive number).
*/
struct person *find_extreme(struct persons *persons, int sign);

/**
* @brief Generates all combinations of numbers and saves them to the given array.
*
* @param array_index index in the <result> array from which
* on the next combination is to be written to
* @param curr_combination combination that is currently being created
* @param curr_index index to which the next number of the current
* combination is to be written to
* @param curr_number current number
* @param persons_count number of all persons
* @param result array with all possible combinations
* (combinations are not divided in any way, use subset_size to divide them)
* @param subset_size size of a combination
*/
void generate_combinations(int subset_size, const int *persons_count, int result[], int curr_number, int curr_index, int curr_combination[], int *array_index);

/**
* @brief Computes the combination number nCk.
*
* @param n all elements
* @param k number of elements in a combination
*/
int combinations_count(int n, int k);

#endif //SETTLING_H
