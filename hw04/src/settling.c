#include "settling.h"

#include "big_int.h"
#include "currency.h"
#include "errors.h"
#include "persons.h"

#include <assert.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct person *find_extreme(struct persons *persons, int sign)
{
    if (!persons->size)
        return NULL;
    struct person *extreme = &persons->persons[0];
    for (int i = 1; i < persons->size; ++i) {
        if (big_int_cmp(&persons->persons[i].amount, &extreme->amount, sign) == sign)
            extreme = &persons->persons[i];
    }
    return extreme;
}

void settle_debt(struct persons *persons, struct currency_table *table)
{
    for (int i = 0; i < persons->size; i++) {
        struct person *debtor = find_extreme(persons, -1);
        struct person *creditor = find_extreme(persons, 1);

        big_int amount;
        big_int_init(&amount);
        big_int_subtract(&amount, &debtor->amount, &amount);

        if (big_int_cmp(&amount, &creditor->amount, 1) == 1)
            amount = creditor->amount;
        big_int_round(&amount);
        if (big_int_is_zero(&amount, 1)) {
            return;
        }

        big_int_add(&debtor->amount, &amount, &debtor->amount);
        if (big_int_is_zero(&debtor->amount, 8) && debtor->amount.digits[17] == 5) {
            debtor->amount.digits[17] = 0;
        }
        big_int_subtract(&creditor->amount, &amount, &creditor->amount);
        if (big_int_is_zero(&creditor->amount, 8) && creditor->amount.digits[17] == 5) {
            creditor->amount.digits[17] = 0;
        }

        printf("%s (%s) -> %s (%s): ", debtor->name, debtor->id, creditor->name, creditor->id);
        big_int_print(&amount);
        printf(" %s\n", table->main_currency);
    }
}

int combinations_count(int n, int k)
{
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    return combinations_count(n - 1, k - 1) + combinations_count(n - 1, k);
}

void generate_combinations(const int subset_size, const int *persons_count, int result[], int curr_number, int curr_index, int curr_combination[], int *array_index)
{
    if (curr_index == subset_size) {
        for (int i = 0; i < subset_size; i++) {
            result[*array_index] = curr_combination[i];
            (*array_index)++;
        }
        return;
    }

    if (curr_number >= *persons_count) {
        return;
    }

    curr_combination[curr_index] = curr_number;
    generate_combinations(subset_size, persons_count, result, curr_number + 1, curr_index + 1, curr_combination, array_index);
    curr_combination[curr_index] = -1;
    generate_combinations(subset_size, persons_count, result, curr_number + 1, curr_index, curr_combination, array_index);
}

void settle_effectively(struct persons *persons, struct currency_table *table)
{
    // works similarly to the master's thesis
    if (persons->size > 19) {
        settle_debt(persons, table);
    }

    int k = 2;
    int not_settled = persons->size;
    bool settled[persons->size];
    memset(settled, false, persons->size);
    while (k <= not_settled) {
        // count how many combinations will be computed
        int total_combinations = combinations_count(persons->size, k);

        int(*combinations) = malloc(total_combinations * k * sizeof(int));
        memset(combinations, -1, total_combinations * k * sizeof(int));
        OP(combinations, ALLOCATION_FAILED);

        int array_index = 0;
        int *curr_combination = malloc(k * sizeof(int));
        if (!curr_combination) {
            free(combinations);
            error_happened(ALLOCATION_FAILED);
            return;
        }
        memset(curr_combination, -1, k * sizeof(int));

        generate_combinations(k, &persons->size, combinations, 0, 0, curr_combination, &array_index);
        free(curr_combination);

        array_index = 0;

        for (int i = 0; i < total_combinations; i++) {
            struct persons subgroup;
            memset(&subgroup, 0, sizeof(subgroup));
            init_persons(&subgroup, k);
            big_int sum;
            big_int_init(&sum);

            // create structure with chosen subgroup
            for (int j = 0; j < k; j++, array_index++) {
                // skip combinations with persons that are already settled
                if (settled[combinations[array_index]]) {
                    array_index = array_index - j + k;
                    break;
                }
                subgroup.persons[j] = persons->persons[combinations[array_index]];
                big_int_add(&sum, &subgroup.persons[j].amount, &sum);
                subgroup.size++;
            }

            // settle subgroup and mark as settled
            if (big_int_is_zero(&sum, 8) && subgroup.size == k) {
                settle_debt(&subgroup, table);
                for (int j = 1; j <= k; j++) {
                    settled[combinations[array_index - j]] = true;
                }
                not_settled -= k;
            }

            free(subgroup.persons);
            subgroup.size = 0;
        }

        free(combinations);
        k++;
    }
}
