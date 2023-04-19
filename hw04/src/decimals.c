#include "errors.h"

#include <stdio.h>
#include <string.h>

static int normalize(int number, char str[4], int decimals)
{
    for (size_t i = 0; i < decimals - strlen(str); i++) {
        number *= 10;
    }
    return number;
}

long decimals_to_base(int decimals)
{
    int base = 1;
    while (decimals-- > 0)
        base *= 10;
    return base;
}

long load_decimal(const char *string, int decimals)
{
    long base = decimals_to_base(decimals);
    if (!strchr(string, '.')) {
        long result;
        int parsed = sscanf(string, "%ld", &result);
        OP(parsed == 1, INVALID_NUMBER_IN_FILE);
        return result * base;
    }

    long large;
    char small[5];
    memset(small, 0, 5);
    int parsed = sscanf(string, "%ld.%4s", &large, small);
    OP(parsed == 2, INVALID_NUMBER_IN_FILE);

    int small_num;
    sscanf(small, "%d", &small_num);

    return large * base + normalize(small_num, small, decimals);
}
