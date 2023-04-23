#include "libs/cut.h"
#include "libs/utils.h"
#include "libs/mainwrap.h"

#define PERSONS_BONUS "tests/data/extra/advanced/persons_bonus.txt"
#define CURRENCIES_BONUS "tests/data/extra/advanced/currencies_bonus.txt"
#define PAYMENTS_BONUS "tests/data/extra/advanced/payments_bonus.txt"

/*
 * You can use this file for your tests.
 * All tests will compile together into one binary.
 * You can also delete your colleagues test files,
 * if you decide not to use them.
 */

TEST(my_test)
{
    int rv = 0;
    CHECK(app_main_args("--bonus", PERSONS_BONUS, CURRENCIES_BONUS, PAYMENTS_BONUS) == rv);
    /* use app_main() if you don't want to give any args */

    const char *correct_output = "Beta (B) -> Adam (A): 2.50 CROWN\n"
                                 "Cyril (C) -> Adam (A): 2.50 CROWN\n"
                                 "Evzen (E) -> Dezko (D): 2 CROWN\n"
                                 "Fero (F) -> Dezko (D): 2 CROWN\n"
                                 "Gertruda (G) -> Dezko (D): 2 CROWN\n"
                                 "Herman (H) -> Dezko (D): 2 CROWN\n"
                                 "Iveta (I) -> Dezko (D): 2 CROWN\n"
                                 "Jozef (J) -> Dezko (D): 2 CROWN\n"
                                 "Kamil (K) -> Dezko (D): 2 CROWN\n"
                                 "Lucia (L) -> Dezko (D): 2 CROWN\n"
                                 "Margita (M) -> Dezko (D): 2 CROWN\n"
                                 "Norbert (N) -> Dezko (D): 2 CROWN\n"
                                 "Otakar (O) -> Dezko (D): 2 CROWN\n"
                                 "Premysl (P) -> Dezko (D): 2 CROWN\n";

    CHECK_NOT_EMPTY(stdout);
    ASSERT_FILE(stdout, correct_output);
    CHECK_IS_EMPTY(stderr);
}
