#include "constants.h"
#include "currency.h"
#include "decimals.h"
#include "errors.h"
#include "persons.h"
#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int semicolon(int letter)
{
    return letter == ';';
}

bool validate_amount(char *amount, bool negative_allowed)
{
    if (*amount == '-') {
        if (!negative_allowed) {
            return false;
        }
        amount++;
    } else if (*amount == '+') {
        amount++;
    }

    if (*amount == 0) {
        return false;
    }

    bool dot = false;
    while (*amount != 0) {
        // count dots
        if (*amount == '.') {
            if (dot) {
                return false;
            }
            dot = true;

        } else if (!isdigit(*amount)) {
            return false;
        }
        amount++;
    }
    return true;
}

bool validate_id(const char *id)
{
    while (*id != 0) {
        if (!isalnum(*id)) {
            return false;
        }
        id++;
    }
    return true;
}

void load_currency_table(struct currency_table *table, FILE *input)
{
    stack_frame();
    char *line = NULL;

    if (read_error_point()) {
        if (line != NULL) {
            free(line);
        }
        leave();
    }

    for (; !feof(input); free(line)) {
        line = read_line(input);
        size_t line_length = strlen(line);
        if (empty_string(line))
            continue;
        char *end;

        char *name = trim_string(line, NULL);
        end = words_end(name);
        *end = '\0';
        OP(validate_id(name), INVALID_CURRENCY_ID);

        char *rating = trim_string(end + 1, NULL);
        end = words_end(rating);
        *end = '\0';
        OP(validate_amount(rating, false), INVALID_RATING);

        if (end + 1 <= line + line_length - 1) {
            OP(empty_string(end + 1), INVALID_RATING);
        }
        add_currency(table, name, load_decimal(rating, RATING_DECIMALS));
    }
    line = NULL;
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
        size_t line_length = strlen(line);
        char *end;

        char *id = trim_string(line, NULL);
        end = words_end(id);
        *end = '\0';
        OP(validate_id(id), INVALID_PERSON_ID);

        OP(end < line + line_length, INVALID_PERSON_NAME);
        char *name = trim_string(end + 1, &end);
        *end = '\0';
        OP(strlen(name) > 0, INVALID_PERSON_NAME);

        add_person(persons, id, name);
    }
    line = NULL;
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
        OP(validate_amount(amount, true), INVALID_AMOUNT);

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
