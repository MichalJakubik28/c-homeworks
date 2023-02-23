#define CUT
#define CUT_MAIN
#include "cut.h"

/* Regular ‹main()› function wrapper. */
#define main _test_main

/* Do «NOT» ever include ‹.c› files in production code!
 * It is a dirty hack to allow us to call your ‹main()›
 * from tests. It should «never» be used otherwise. */

#include "drawer.c"
#undef main

TEST(basic_run_positive)
{
    draw_line(10);
    ASSERT_FILE(stdout, "##########\n");
}

TEST(basic_run_0)
{
    draw_line(0);
    ASSERT_FILE(stdout, "\n");
}

TEST(basic_run_negative)
{
    draw_line(-5);
    ASSERT_FILE(stdout, "");
}

// You should comment what is being tested.
TEST(name_of_the_test)
{
    // Place your calls in here, e.g.
    draw_line(10000);

    // You can check standard output of the program using ‹ASSERT_FILE› with
    // ‹stdout›.
    ASSERT_FILE(stdout, "10 thousand # should be here\n");
}

// You can also check the whole run of a program.
TEST(name_of_the_test_for_whole_program)
{
    // Using ‹INPUT_STRING› you can define standard input for the program, as if
    // you were typing it in a terminal.
    INPUT_STRING("10");

    // You can call the ‹main› function and also store the status code it
    // returned.
    int status = _test_main();

    // Then you can check if the status code meets your expectations along with
    // the standard output, if you wish so.
    ASSERT((status) == 0);
    ASSERT_FILE(stdout, "Hello world!\n");
}
