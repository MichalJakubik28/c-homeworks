/*
 * You can use this file for your own tests
 */

#include "libs/cut.h"
#include "libs/mainwrap.h"
#include "libs/utils.h"

#include <stdlib.h>

#define CONTAINERS_FILE "tests/data/example-containers.csv"
#define PATHS_FILE "tests/data/example-paths.csv"
#define EMPTY_FILE "tests/data/empty_file.csv"
#define CONTAINERS1 "tests/data/containers1.csv"
#define PATHS1 "tests/data/paths1.csv"
#define CONT_BAD_ID "tests/data/cont_bad_id.csv"
#define CONT_DUP_ID "tests/data/cont_dup_id.csv"
#define CONT_BAD_X "tests/data/cont_bad_x.csv"
#define CONT_BAD_Y "tests/data/cont_bad_y.csv"
#define CONT_BAD_NUMBER "tests/data/cont_bad_number.csv"
#define CONT_BAD_WASTE "tests/data/cont_bad_waste.csv"
#define CONT_BAD_CAPACITY "tests/data/cont_bad_capacity.csv"
#define CONT_TOO_BIG_DEC_X "tests/data/cont_too_big_dec_x.csv"
#define PATH_NONEXISTENT_X "tests/data/path_nonexistent_x.csv"
#define PATH_NONEXISTENT_Y "tests/data/path_nonexistent_y.csv"
#define PATH_TOO_BIG "tests/data/path_too_big.csv"
#define CONT_BAD_ACCESS "tests/data/cont_bad_access.csv"

/* The following “extentions” to CUT are available in this test file:
 *
 * • ‹CHECK_IS_EMPTY(file)› — test whether the file is empty.
 * • ‹CHECK_NOT_EMPTY(file)› — inverse of the above.
 *
 * • ‹app_main_args(ARG…)› — call your ‹main()› with given arguments\n.
 * • ‹app_main()› — call your ‹main()› without any arguments\n. */

TEST(base_test)
{
    int rv = 0;
    CHECK(app_main_args(CONTAINERS_FILE, PATHS_FILE) == rv);

    

    const char *correct_output =
        "ID: 1, Type: Colored glass, Capacity: 1550, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 2, Type: Clear glass, Capacity: 1550, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 3, Type: Plastics and Aluminium, Capacity: 1100, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 4, Type: Colored glass, Capacity: 900, Address: Drozdi 55, Neighbors: 1 2 3 5 8\n"
            "ID: 5, Type: Paper, Capacity: 5000, Address: Klimesova 60, Neighbors: 4 8\n"
            "ID: 6, Type: Colored glass, Capacity: 3000, Address: Klimesova 60, Neighbors: 8\n"
            "ID: 7, Type: Plastics and Aluminium, Capacity: 5000, Address: Klimesova 60, Neighbors: 8\n"
            "ID: 8, Type: Biodegradable waste, Capacity: 3000, Address: Na Buble 5, Neighbors: 4 5 6 7 11\n"
            "ID: 9, Type: Textile, Capacity: 500, Address: Na Buble 5, Neighbors: 10\n"
            "ID: 10, Type: Plastics and Aluminium, Capacity: 900, Address: Odlehla 70, Neighbors: 9\n"
            "ID: 11, Type: Paper, Capacity: 2000, Address: Odlehla 70, Neighbors: 8\n"
    ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "" /* STDERR is empty*/);
}

TEST(empty_files)
{
    int rv = 0;
    CHECK(app_main_args(EMPTY_FILE, EMPTY_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "" /* STDERR is empty*/);
}

TEST(invalid_arg1)
{
    int rv = 1;
    CHECK(app_main_args("-g", "-s", CONTAINERS_FILE, PATHS_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Invalid -g argument\n");
}

TEST(invalid_arg2)
{
    int rv = 1;
    CHECK(app_main_args("-t", "-p", "-c", "-s", CONTAINERS_FILE, PATHS_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Invalid waste type filter parameter\n");
}

TEST(invalid_arg3)
{
    int rv = 1;
    CHECK(app_main_args("-t", "-p", "-c", "-g", CONTAINERS_FILE, PATHS_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Invalid waste type filter parameter\n");
}

TEST(invalid_arg4)
{
    int rv = 1;
    CHECK(app_main_args(PATHS_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(invalid_arg5)
{
    int rv = 1;
    CHECK(app_main_args("-t", "-p", "-c", PATHS_FILE) == rv);

    

    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not initialize files\n");
}

TEST(invalid_arg6)
{
    int rv = 1;
    CHECK(app_main_args("-t", "-p", "-t", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(invalid_arg7)
{
    int rv = 1;
    CHECK(app_main_args("-t", "AAAAAAAAAAAAAAAAAPPPPPPPPPPPPPPPPPPPPPPPPPPCCCCCCCCCCCCCCCCCCCCCCCCCCGGGGGGGGGGGGGGGGGGGGGTTTTTTTTTTTTTTTBBBBBBBBBkB", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Invalid waste type filter parameter\n");
}

TEST(invalid_arg8)
{
    int rv = 1;
    CHECK(app_main_args("-t", "A", "-t", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(invalid_arg9)
{
    int rv = 1;
    CHECK(app_main_args("-s", "-s", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(invalid_arg10)
{
    int rv = 1;
    CHECK(app_main_args("-c", "100-200", "-c", "100-300", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(invalid_arg11)
{
    int rv = 1;
    CHECK(app_main_args("-g", "1,2", "-g", "1,2", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not parse input - invalid or not enough arguments\n");
}

TEST(sample1)
{
    int rv = 0;
    CHECK(app_main_args(CONTAINERS1, EMPTY_FILE) == rv);


    const char *correct_output =
            "ID: 1, Type: Colored glass, Capacity: 2000, Address: TEST 44, Neighbors:\n"
            "ID: 2, Type: Textile, Capacity: 2000, Address: TEST 44, Neighbors:\n"
            "ID: 3, Type: Paper, Capacity: 2000, Address: TEST 4446, Neighbors:\n"
            "ID: 4, Type: Biodegradable waste, Capacity: 2000, Address: TEST, Neighbors:\n"
            "ID: 5, Type: Plastics and Aluminium, Capacity: 2000, Address: TESTik 44, Neighbors:\n"
            "ID: 128, Type: Clear glass, Capacity: 2000, Address:, Neighbors:\n"
            "ID: 129, Type: Clear glass, Capacity: 1, Address: 124, Neighbors:\n"

            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "");
}

TEST(sample2)
{
    int rv = 0;
    CHECK(app_main_args("-s", CONTAINERS1, EMPTY_FILE) == rv);


    const char *correct_output =
            "1;CT;\n"
            "2;P;\n"
            "3;B;\n"
            "4;A;\n"
            "5;G;\n"
            "6;G;\n"
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "");
}

TEST(sample3)
{
    int rv = 0;
    CHECK(app_main_args("-g", "1,4", CONTAINERS1, PATHS1) == rv);


    const char *correct_output =
            "1-2-3-4 1000\n"
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "");
}

TEST(invalid_path)
{
    int rv = 1;
    CHECK(app_main_args("-g", "1,10", CONTAINERS1, PATHS1) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Invalid start or target point\n");
}

TEST(sample4)
{
    int rv = 0;
    CHECK(app_main_args("-g", "1,4", CONTAINERS1, EMPTY_FILE) == rv);


    const char *correct_output =
            "No path between specified sites\n"
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "");
}

TEST(invalid_containers)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_ID, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers2)
{
    int rv = 1;
    CHECK(app_main_args(CONT_DUP_ID, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers3)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_X, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers4)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_Y, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers5)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_NUMBER, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers6)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_WASTE, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers7)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_CAPACITY, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers8)
{
    int rv = 1;
    CHECK(app_main_args(CONT_TOO_BIG_DEC_X, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_containers9)
{
    int rv = 1;
    CHECK(app_main_args(CONT_BAD_ACCESS, EMPTY_FILE) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load containers\n");
}

TEST(invalid_paths1)
{
    int rv = 1;
    CHECK(app_main_args(CONTAINERS_FILE, PATH_NONEXISTENT_X) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load paths\n");
}

TEST(invalid_paths2)
{
    int rv = 1;
    CHECK(app_main_args(CONTAINERS_FILE, PATH_NONEXISTENT_Y) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load paths\n");
}

TEST(invalid_paths3)
{
    int rv = 1;
    CHECK(app_main_args(CONTAINERS_FILE, PATH_TOO_BIG) == rv);


    const char *correct_output =
            ""
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "Could not load paths\n");
}

TEST(filter_test)
{
    int rv = 0;
    CHECK(app_main_args("-t", "AGCPT", "-c", "1000-5000", "-p", "Y", CONTAINERS_FILE, PATHS_FILE) == rv);


    const char *correct_output =
            "ID: 1, Type: Colored glass, Capacity: 1550, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 2, Type: Clear glass, Capacity: 1550, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 3, Type: Plastics and Aluminium, Capacity: 1100, Address: Drozdi 55, Neighbors: 4\n"
            "ID: 11, Type: Paper, Capacity: 2000, Address: Odlehla 70, Neighbors: 8\n"
            ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "");
}
