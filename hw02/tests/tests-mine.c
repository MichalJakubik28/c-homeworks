#define CUT

#include "libs/cut.h"
#include "libs/mainwrap.h"

#include <stdlib.h>

/* Here, you can write your own tests
 *
 * Suggestions:
 *    - more complex combinations, such as triples
 *    - more incorrect inputs
 *
 * For bonus tests with arguments, use ‹app_main_args(ARGUMENTS…)›
 * instead of ‹app_main()›. */

TEST(empty) {
    INPUT_STRING(
            ""
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(high_card) {
    INPUT_STRING(
            "Ah 3h\n"
            "5d 6s\n"
            "Qh 8d 9s Tc Qc\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 1\n");
}

TEST(high_card_invalid_sep_end) {
    INPUT_STRING(
            "Ah 3h\n"
            "5d 6s\n"
            "Qh 8d 9s Tc Qc"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(straight_vs_straight1) {
    INPUT_STRING(
            "Th Jh\n"
            "3d 4s\n"
            "5h 6d 7s 8c 9c\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 1\n");
}

TEST(straight_vs_straight2) {
    INPUT_STRING(
            "Th Jh\n"
            "Td Js\n"
            "5h 6d 7s 8c 9c\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Draw\n");
}

TEST(straight_flush_vs_foak) {
    INPUT_STRING(
            "Ts Js\n"
            "5c 5s\n"
            "5h 5d 7s 8s 9s\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 1\n");
}

TEST(full_house_vs_pair) {
    INPUT_STRING(
            "Qs Js\n"
            "5c 5s\n"
            "5h 8d 8s Tc 9s\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 2\n");
}

TEST(full_house_vs_two_pair) {
    INPUT_STRING(
            "Ts Js\n"
            "5c 5s\n"
            "5h 8d 8s Tc 9s\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 2\n");
}

TEST(flush_vs_baby_straight) {
    INPUT_STRING(
            "Ac 2s\n"
            "2c 6c\n"
            "Tc 8c 5c 4s 3s\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 2\n");
}

TEST(toak_vs_two_pair) {
    INPUT_STRING(
            "Ac As\n"
            "2c 6c\n"
            "2d 6d 5c 4s Ad\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 1\n");
}

TEST(steel_wheel_vs_pair) {
    INPUT_STRING(
            "Ac Qs\n"
            "2d 3d\n"
            "4d 6d 5d Ts Ad\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Player 2\n");
}

TEST(same) {
    INPUT_STRING(
            "Ac Qc\n"
            "Ad Qd\n"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "Draw\n");
}

TEST(error1) {
    INPUT_STRING(
            "Ac Qc\n"
            "Ad Qd"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error2) {
    INPUT_STRING(
            "Ac Q"
            "Ad Qd\n"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error3) {
    INPUT_STRING(
            "Ac\n"
            "Ad Qd\n"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error4) {
    INPUT_STRING(
            "A A\n"
            "Ad Qd\n"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error5) {
    INPUT_STRING(
            "Ac Ad\n"
            "Ad Qd\n"
            "2s 3s 4s 5s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}


TEST(error6) {
    INPUT_STRING(
            "Ac As\n"
            "Ad Qd\n"
            "2s 3s 4s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error7) {
    INPUT_STRING(
            "   pa Ac As\n"
            "Ad Qd\n"
            "2s 3s 4s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}

TEST(error8) {
    INPUT_STRING(
            "5c Ac As\n"
            "Ad Qd\n"
            "2s 3s 4s 6d\n"
    );

    app_main();
    ASSERT_FILE(stdout, "");
}
/* A test template: */


//TEST(template) {
//    INPUT_STRING(
//        "PLAYER 1 CARDS\n"
//        "PLAYER 2 CARDS\n"
//        "BOARD CARDS\n"
//    );
//
//    // TODO: Choose the proper main:
//    // 1. For basic functionality, use this function:
//    app_main();
//    // 2: For bonus functionality with program arguments, use this instead:
//    app_main_args("ARGUMENT1", "ARGUMENT2", ...);
//
//    ASSERT_FILE(stdout, "EXPECTED OUTPUT\n");
//}

