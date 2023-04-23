#include "currency.h"
#include "errors.h"
#include "load.h"
#include "persons.h"
#include "settling.h"

#include <stdlib.h>
#include <string.h>

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
        object_destroy(&currency_table);
        object_destroy(&persons);

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
    init_persons(&persons, 16);

    // posunut argv o 1 pre bonus

    OP(person_file = fopen(argv[1 + bonus], "r"), INVALID_ARGUMENTS);
    load_persons(&persons, person_file);

    OP(currency_file = fopen(argv[2 + bonus], "r"), INVALID_ARGUMENTS);
    load_currency_table(&currency_table, currency_file);

    OP(payment_file = fopen(argv[3 + bonus], "r"), INVALID_ARGUMENTS);
    load_payments(&persons, &currency_table, payment_file);

    if (bonus == 1) {
        settle_effectively(&persons, &currency_table);
    } else {
        settle_debt(&persons, &currency_table);
    }

    exit_success();

    // fix for compiler warning
    return EXIT_SUCCESS;
}
