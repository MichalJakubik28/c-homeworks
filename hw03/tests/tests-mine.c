/*
 * You can use this file for your own tests
 */

#include "libs/cut.h"
#include "libs/mainwrap.h"
#include "libs/utils.h"

#include <stdlib.h>

#define CONTAINERS_FILE "data/Brno-JehniceContainers.csv"
#define PATHS_FILE "data/Brno-JehnicePaths.csv"

/* The following “extentions” to CUT are available in this test file:
 *
 * • ‹CHECK_IS_EMPTY(file)› — test whether the file is empty.
 * • ‹CHECK_NOT_EMPTY(file)› — inverse of the above.
 *
 * • ‹app_main_args(ARG…)› — call your ‹main()› with given arguments.
 * • ‹app_main()› — call your ‹main()› without any arguments. */

TEST(my_test)
{
    int rv = 0; /* return value of main()*/
    CHECK(app_main_args(CONTAINERS_FILE, PATHS_FILE /*, arguments for main() */) == rv);

    /* TIP: Use ‹app_main()› to test the program without arguments. */

    const char *correct_output =
        "ID: 18388, Type: Plastics and Aluminium, Capacity: 1100, Address: Havlaskova 244, Neighbors: 5229 5230 5232 5233 6322 6323 10828 14420 18389 18390 18511 22102 24948 24949\n"
            "ID: 20637, Type: Paper, Capacity: 1100, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 13396, Type: Plastics and Aluminium, Capacity: 1100, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 12922, Type: Paper, Capacity: 1100, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 8007, Type: Clear glass, Capacity: 1125, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 11164, Type: Plastics and Aluminium, Capacity: 1100, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 8006, Type: Colored glass, Capacity: 1125, Address: Havlaskova 244, Neighbors: 6323 24948\n"
            "ID: 6323, Type: Clear glass, Capacity: 1125, Address: Lelekovicka 115, Neighbors: 5229 5230 5232 5233 8006 8007 10828 11164 12922 13396 14420 18388 18511 20637 22102 24948 24949\n"
            "ID: 18390, Type: Plastics and Aluminium, Capacity: 1100, Address: Lelekovicka 115, Neighbors: 18388 24948\n"
            "ID: 6322, Type: Colored glass, Capacity: 1125, Address: Lelekovicka 115, Neighbors: 18388 24948\n"
            "ID: 18389, Type: Paper, Capacity: 1100, Address: Lelekovicka 115, Neighbors: 18388 24948\n"
            "ID: 24948, Type: Plastics and Aluminium, Capacity: 1100, Address: Plastky 47, Neighbors: 6322 6323 8006 8007 11164 12922 13396 18388 18389 18390 20637\n"
            "ID: 5229, Type: Colored glass, Capacity: 2500, Address: Plastky 47, Neighbors: 6323 18388\n"
            "ID: 5230, Type: Clear glass, Capacity: 2500, Address: Plastky 47, Neighbors: 6323 18388\n"
            "ID: 24949, Type: Plastics and Aluminium, Capacity: 1100, Address: Plastky 47, Neighbors: 6323 18388\n"
            "ID: 22102, Type: Textile, Capacity: 1000, Address: Plastky 47, Neighbors: 6323 18388\n"
            "ID: 18511, Type: Plastics and Aluminium, Capacity: 1100, Address: Oresinska 278, Neighbors: 6323 18388\n"
            "ID: 5232, Type: Colored glass, Capacity: 1125, Address: Oresinska 278, Neighbors: 6323 18388\n"
            "ID: 5233, Type: Clear glass, Capacity: 1125, Address: Oresinska 278, Neighbors: 6323 18388\n"
            "ID: 10828, Type: Plastics and Aluminium, Capacity: 1100, Address: Oresinska 278, Neighbors: 6323 18388\n"
            "ID: 14420, Type: Paper, Capacity: 1100, Address: Oresinska 278, Neighbors: 6323 18388\n"
    ;

    ASSERT_FILE(stdout, correct_output);
    CHECK_FILE(stderr, "" /* STDERR is empty*/);
}
