#include "libs/cut.h"
#include "libs/utils.h"
#include "libs/mainwrap.h"
#include "../src/big_int.h"

#include <string.h>


TEST(big_int_init) {
    big_int item1;
    big_int_init(&item1);
    CHECK(item1.is_positive);
    CHECK(item1.digits[0] == 0);
    CHECK(item1.digits[24] == 0);

    SUBTEST(init_number) {
        big_int to_add;
        big_int_init(&to_add);
        big_int_convert(&to_add, 123456789012123456);
        big_int_print(&to_add);
        ASSERT_FILE(stdout, "123456789012.12");
        CHECK(to_add.is_positive);
    }
}

TEST(big_int_add) {
    big_int item1;
    big_int_init(&item1);
    big_int to_add;
    big_int_init(&to_add);
    big_int_convert(&to_add, 123456789012123456);


    SUBTEST(add_number) {
        big_int_add(&item1, &to_add, &item1);
        big_int_print(&item1);
        ASSERT_FILE(stdout, "123456789012.12");
        CHECK(to_add.is_positive);
    }

    SUBTEST(add_number2) {
            big_int_convert(&item1, 123000000);
            big_int_convert(&to_add, 456000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "579");
        }

    SUBTEST(add_number3) {
            big_int_convert(&item1, -123000000);
            big_int_convert(&to_add, 456000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "333");
        }

    SUBTEST(add_number4) {
            big_int_convert(&item1, -456000000);
            big_int_convert(&to_add, 123000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-333");
        }

    SUBTEST(add_number5) {
            big_int_convert(&item1, -456000000);
            big_int_convert(&to_add, -123000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-579");
        }

    SUBTEST(add_number6) {
            big_int_convert(&item1, 123000000);
            big_int_convert(&to_add, -456000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-333");
        }

    SUBTEST(add_number7) {
            big_int_convert(&item1, 0);
            big_int_convert(&to_add, 0);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "0");
        }

    SUBTEST(add_number7) {
            big_int_convert(&item1, 123456789);
            big_int_convert(&to_add, 234567891);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "358.02");
        }

    SUBTEST(add_number8) {
            big_int_convert(&item1, 456000000);
            big_int_convert(&to_add, -123000000);
            big_int_add(&item1, &to_add, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "333");
        }
}

TEST(big_int_subtract) {
    big_int item1;
    big_int_init(&item1);
    big_int to_subtract;
    big_int_init(&to_subtract);

    SUBTEST(subtract_number1) {
            big_int_convert(&item1, 123456789012345678);
            big_int_convert(&to_subtract, 123456789012345678);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "0");
    }

    SUBTEST(subtract_number2) {
            big_int_convert(&item1, 123000000);
            big_int_convert(&to_subtract, 456000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-333");
        }

    SUBTEST(subtract_number3) {
            big_int_convert(&item1, -123000000);
            big_int_convert(&to_subtract, 456000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-579");
        }

    SUBTEST(subtract_number4) {
            big_int_convert(&item1, -456000000);
            big_int_convert(&to_subtract, 123000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-579");
        }

    SUBTEST(subtract_number5) {
            big_int_convert(&item1, -456000000);
            big_int_convert(&to_subtract, -123000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-333");
        }

    SUBTEST(subtract_number6) {
            big_int_convert(&item1, 123000000);
            big_int_convert(&to_subtract, -456000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "579");
        }

    SUBTEST(subtract_number7) {
            big_int_convert(&item1, 0);
            big_int_convert(&to_subtract, 0);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "0");
        }

    SUBTEST(subtract_number7) {
            big_int_convert(&item1, 123456789);
            big_int_convert(&to_subtract, 234567891);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-111.11");
        }

    SUBTEST(subtract_number5) {
            big_int_convert(&item1, -123000000);
            big_int_convert(&to_subtract, -456000000);
            big_int_subtract(&item1, &to_subtract, &item1);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "333");
        }
}

TEST(big_int_divide) {
    big_int item1;
    big_int_init(&item1);
    big_int to_divide;
    big_int_init(&to_divide);

    SUBTEST(divide_number1) {
            big_int_convert(&item1, 123456789012345678);
            big_int_div_by_int(&item1, &item1, 10);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "12345678901.23");
        }

    SUBTEST(divide_number2) {
            big_int_convert(&item1, 10000000);
            big_int_div_by_int(&item1, &item1, 3);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "3.33");
        }

    SUBTEST(divide_number3) {
            big_int_convert(&item1, 123456789012345678);
            big_int_div_by_int(&item1, &item1, -10);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-12345678901.23");
        }

    SUBTEST(divide_number4) {
            big_int_convert(&item1, 1234000000);
            big_int_div_by_int(&item1, &item1, -1234);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-1");
        }

    SUBTEST(divide_number5) {
            big_int_convert(&item1, -1234000000);
            big_int_div_by_int(&item1, &item1, 1234);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "-1");
        }

    SUBTEST(divide_number6) {
            big_int_convert(&item1, 1234000000);
            big_int_div_by_int(&item1, &item1, 12340);
            big_int_print(&item1);
            ASSERT_FILE(stdout, "0.10");
        }
}

TEST(big_int_is_zero) {
    big_int item1;
    big_int_init(&item1);
    CHECK(big_int_is_zero(&item1, 0));
    big_int_convert(&item1, 1);
    CHECK(!big_int_is_zero(&item1, 2));
}

TEST(rounding) {
    big_int item1;
    big_int_init(&item1);
    big_int_convert(&item1, 1999999);
    big_int_round(&item1);
    big_int_print(&item1);
    ASSERT_FILE(stdout, "2");
}
