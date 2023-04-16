#include <stdio.h>
#include <string.h>

static int normalize(int number, char str[4])
{
    for (int i = 0; i < 4 - strlen(str); i++) {
        number *= 10;
    }
    return number;
}

int decimals_to_base(int decimals)
{
    int base = 1;
    while (decimals --> 0)
        base *= 10;
    return base;
}

int load_decimal(const char *string, int decimals)
{
    int base = decimals_to_base(decimals);
    if (!strchr(string, '.')) {
        int result;
        sscanf(string, "%d  ", &result);
        return result * base;
    }

    int large;
    char small[5];
    memset(small, 0, 5);
    sscanf(string, "%d.%4s", &large, small);
    int small_num;
    sscanf(small, "%d", &small_num);

    return large * base + normalize(small_num, small);
}
