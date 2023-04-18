#include "currency.h"
#include "errors.h"
#include "load.h"
#include "persons.h"


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
            // urobi sa kopia?
            amount = creditor->amount;
        if (big_int_is_zero(&amount, 7)) {
            return;
        }

        big_int_add(&debtor->amount, &amount, &debtor->amount);
        big_int_subtract(&creditor->amount, &amount, &creditor->amount);

        printf("%s (%s) -> %s (%s): ", debtor->name, debtor->id, creditor->name, creditor->id);
        big_int_print(&amount);
        printf(" %s\n", table->main_currency);
    }
}

int main(int argc, char **argv)
{
    stack_top_frame();
    enum error_codes error_code;
    struct currency_table currency_table;
    struct persons persons;
    FILE *person_file = NULL;
    FILE *currency_file = NULL;
    FILE *payment_file = NULL;
    memset(&currency_table, 0, sizeof(currency_table));
    memset(&persons, 0, sizeof(persons));

    if ((error_code = read_error_point())) {
        // nie je ta funkcia prazdna?
        // edit: je, ale to nevadi
        object_destroy(&currency_table);
        object_destroy(&persons);

        // skontroluje ci file nie je null a zavrie ho
        if (person_file != NULL) {
            fclose(person_file);
        }
        if (currency_file != NULL) {
            fclose(currency_file);
        }
        if (payment_file != NULL) {
            fclose(payment_file);
        }

        if (error_code != SUCCESS)
            print_error_message(error_code);

        return return_code(error_code);
    }

    OP(argc >= 4, INVALID_ARGUMENTS);
    int bonus = strcmp(argv[1], "--bonus") == 0 ? 1 : 0;
    if (bonus == 1) {
        OP(argc == 5, INVALID_ARGUMENTS);
    } else {
        OP(argc == 4, INVALID_ARGUMENTS);
    }

    init_currency_table(&currency_table);
    init_persons(&persons);

    // posunut argv o 1 pre bonus

    OP(person_file = fopen(argv[1 + bonus], "r"), INVALID_ARGUMENTS);
    load_persons(&persons, person_file);


    OP(currency_file = fopen(argv[2 + bonus], "r"), INVALID_ARGUMENTS);
    load_currency_table(&currency_table, currency_file);

    OP(payment_file = fopen(argv[3 + bonus], "r"), INVALID_ARGUMENTS);
    load_payments(&persons, &currency_table, payment_file);

    if (bonus == 1) {
        printf("Here will be bonus\n");
    } else {
        settle_debt(&persons, &currency_table);
    }

    exit_success();
}
