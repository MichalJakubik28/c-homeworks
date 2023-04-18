#include "constants.h"
#include "currency.h"
#include "decimals.h"
#include "errors.h"
#include "persons.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int semicolon(int letter)
{
    return letter == ';';
}

void load_currency_table(struct currency_table *table, FILE *input)
{
    stack_frame();
    char *line = NULL;

    if (read_error_point()) {
        free(line);
        leave();
    }

    for (; !feof(input); free(line)) {
        line = read_line(input);
        if (empty_string(line))
            continue;
        char *end;

        char *name = trim_string(line, NULL);
        end = words_end(name);
        *end = '\0';

        char *rating = trim_string(end + 1, NULL);
        end = words_end(rating);
        *end = '\0';

        add_currency(table, name, load_decimal(rating, RATING_DECIMALS));
    }
    OP(table->main_currency != NULL, DEFAULT_CURRENCY_NOT_SET);
    leave();
}

void load_persons(struct persons *persons, FILE *input)
{
    stack_frame();
    char *line = NULL;

    if (read_error_point()) {
        free(line);
        leave();
    }

    for (; !feof(input); free(line)) {
        line = read_line(input);
        if (empty_string(line))
            continue;
        char *end;

        char *id = trim_string(line, NULL);
        end = words_end(id);
        *end = '\0';

        char *name = trim_string(end + 1, &end);
        *end = '\0';

        add_person(persons, id, name);
    }
    OP(persons->size > 1, NOT_ENOUGH_PERSONS);
    leave();
}

void load_payments(struct persons *persons, struct currency_table *table, FILE *input)
{
    stack_frame();
    char *line = NULL;

    if (read_error_point()) {
        free(line);
        leave();
    }

    for (; !feof(input); free(line)) {
        line = read_line(input);
        if (empty_string(line))
            continue;
        char *end;

        char *from = trim_string(line, NULL);
        end = words_end(from);
        *end = '\0';

        char *to = trim_string(end + 1, NULL);
        end = words_end(to);
        *end = '\0';

        char *amount = trim_string(end + 1, NULL);
        end = words_end(amount);
        *end = '\0';

        char *currency = trim_string(end + 1, &end);
        *end = '\0';

        long value = convert_currency(table, load_decimal(amount, PAYMENT_DECIMALS), currency);
        big_int enlarged_value;
        big_int_init(&enlarged_value);
        big_int_convert(&enlarged_value, value);
        int from_count = char_count(from, ';') + 1;
        int to_count = char_count(to, ';') + 1;

        char last_char;
        do {
            end = get_token(from, semicolon);
            last_char = *end;

            *end = '\0';

            struct person *p;
            OP(p = find_person(persons, from), PERSON_NOT_FOUND);

            big_int divided;
            big_int_init(&divided);
            big_int_div_by_int(&enlarged_value, &divided, from_count);
            big_int_add(&p->amount, &divided, &p->amount);

            from = end;
        } while (last_char && ++from);

        do {
            end = get_token(to, semicolon);
            last_char = *end;

            *end = '\0';

            struct person *p;
            OP(p = find_person(persons, to), PERSON_NOT_FOUND);

            big_int divided;
            big_int_init(&divided);
            big_int_div_by_int(&enlarged_value, &divided, to_count);
            big_int_subtract(&p->amount, &divided, &p->amount);

            to = end;
        } while (last_char && ++to);
    }
    leave();
}
