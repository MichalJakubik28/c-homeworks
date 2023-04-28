#include "libs/cut.h"
#include "libs/utils.h"
#include "libs/mainwrap.h"
#include "../src/settling.h"

TEST(combinations_count) {
    SUBTEST(10C3) {
        int total_combinations = combinations_count(10, 3);
        ASSERT(total_combinations == 120);
    }
    SUBTEST(3C10) {
            int total_combinations = combinations_count(3, 10);
            ASSERT(total_combinations == 0);
        }
    SUBTEST(19C10) {
            int total_combinations = combinations_count(19, 10);
            ASSERT(total_combinations == 92378);
        }
    SUBTEST(19C9) {
            int total_combinations = combinations_count(19, 9);
            ASSERT(total_combinations == 92378);
        }
    SUBTEST(0C0) {
            int total_combinations = combinations_count(0, 0);
            ASSERT(total_combinations == 1);
        }
}

TEST(combinations) {
    SUBTEST(tuples from three) {
        int k = 2;
        int n = 3;
        int total_combinations = combinations_count(n, k);
        int (*combinations) = malloc(total_combinations * k * sizeof(int));
        memset(combinations, -1, total_combinations * k * sizeof(int));
        OP(combinations, ALLOCATION_FAILED);
        int array_index = 0;
        int *curr_combination = malloc(k * sizeof(int));
        memset(curr_combination, -1, k * sizeof(int));
        generate_combinations(k, &n, combinations, 0, 0, curr_combination, &array_index);
        for (int i = 0; i < total_combinations * k; i++) {
            printf("%d", combinations[i]);
        }
        free(curr_combination);
        free(combinations);
        ASSERT_FILE(stdout, "010212");
    }

    SUBTEST(triples from five) {
            int k = 3;
            int n = 5;
            int total_combinations = combinations_count(n, k);
            int (*combinations) = malloc(total_combinations * k * sizeof(int));
            memset(combinations, -1, total_combinations * k * sizeof(int));
            OP(combinations, ALLOCATION_FAILED);
            int array_index = 0;
            int *curr_combination = malloc(k * sizeof(int));
            memset(curr_combination, -1, k * sizeof(int));
            generate_combinations(k, &n, combinations, 0, 0, curr_combination, &array_index);
            for (int i = 0; i < total_combinations * k; i++) {
                printf("%d", combinations[i]);
            }
            free(curr_combination);
            free(combinations);
            ASSERT_FILE(stdout, "012013014023024034123124134234");
        }

    SUBTEST(foursome from six) {
            int k = 4;
            int n = 6;
            int total_combinations = combinations_count(n, k);
            int (*combinations) = malloc(total_combinations * k * sizeof(int));
            memset(combinations, -1, total_combinations * k * sizeof(int));
            OP(combinations, ALLOCATION_FAILED);
            int array_index = 0;
            int *curr_combination = malloc(k * sizeof(int));
            memset(curr_combination, -1, k * sizeof(int));
            generate_combinations(k, &n, combinations, 0, 0, curr_combination, &array_index);
            for (int i = 0; i < total_combinations * k; i++) {
                printf("%d", combinations[i]);
            }
            free(curr_combination);
            free(combinations);
            ASSERT_FILE(stdout, "012301240125013401350145023402350245034512341235124513452345");
        }
}
