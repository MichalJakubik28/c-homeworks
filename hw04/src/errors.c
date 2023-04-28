#include "errors.h"

#include <stdio.h>
#include <string.h>

static jmp_buf *point;

void set_error_point(jmp_buf *current)
{
    point = current;
}

jmp_buf *get_error_point()
{
    return point;
}

int error_happened(enum error_codes code)
{
    longjmp(*point, code);
}

void exit_success(void)
{
    error_happened(SUCCESS);
}

static const char *resolve_message(enum error_codes code)
{
    static char unknownError[128];
    memset(unknownError, 0, 128);
    switch (code) {
    case INITIAL_PASS:
    case SUCCESS:
        return "OK";
    case DUPLICIT_INITIALIZATION:
        return "duplicit initialization";
    case ALLOCATION_FAILED:
        return "allocation failed";
    case CURRENCY_ALREADY_PRESENT:
        return "currency is already present";
    case CURRENCY_DUPLICATE_MAIN:
        return "duplicated main currency";
    case CURRENCY_NOT_FOUND:
        return "currency not found";
    case DEFAULT_CURRENCY_NOT_SET:
        return "default currency not set";
    case NEGATIVE_CURRENCY_RATING:
        return "negative currency rating found";
    case PERSON_NOT_FOUND:
        return "person not found";
    case PERSON_ALREADY_PRESENT:
        return "person already present";
    case NOT_ENOUGH_PERSONS:
        return "not enough persons in input file";
    case INVALID_NUMBER_IN_FILE:
        return "invalid amount in input files";
    case INVALID_ARGUMENTS:
        return "invalid arguments; use <program> <person-file> <currency-file> <payments-file>";
    case INVALID_PERSON_ID:
        return "invalid person ID";
    case INVALID_CURRENCY_ID:
        return "invalid currency ID";
    case INVALID_AMOUNT:
        return "invalid amount of money in transaction";
    case INVALID_RATING:
        return "invalid currency rating";
    case INVALID_PERSON_NAME:
        return "invalid person name";
    default:
        sprintf(unknownError, "unknown error (%u)", code);
        return unknownError;
    }
}

int return_code(enum error_codes code)
{
    if (code == SUCCESS)
        return 0;
    return code;
}

void print_error_message(enum error_codes code)
{
    fprintf(stderr, "Error happened: %s\n", resolve_message(code));
}
