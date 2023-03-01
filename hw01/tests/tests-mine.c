/*
 * You can write your own tests in this file
 */

#define CUT
#include "libs/cut.h"

#include "libs/mainwrap.h"

#include <stdlib.h>

// Test template just for you ;)

TEST(wrong_switch)
{
    CHECK(app_main("-k") == EXIT_FAILURE);
    CHECK_FILE(stderr, "Unknown argument: -k\n");
}

TEST(zeros4)
{
    const unsigned char input[] = {
            0x00, 0x00, 0x00, 0x00,
    };
    const unsigned char output[] = {
            0x00, 0x00, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(zeros3)
{
    const unsigned char input[] = {
            0x00, 0x00, 0x00
    };
    const unsigned char output[] = {
            0x00, 0x00, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(zeros2)
{
    const unsigned char input[] = {
            0x00, 0x00
    };
    const unsigned char output[] = {
            0x00, 0x00, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(zeros1)
{
    const unsigned char input[] = {
            0x00
    };
    const unsigned char output[] = {
            0x00, 0x00, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs4)
{
    const unsigned char input[] = {
            0xff, 0xff, 0xff, 0xff
    };
    const unsigned char output[] = {
            0x17, 0xff, 0xff, 0xff, 0x7e,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs3)
{
    const unsigned char input[] = {
            0xff, 0xff, 0xff
    };
    const unsigned char output[] = {
            0x3f, 0xff, 0xff, 0xfc, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs2)
{
    const unsigned char input[] = {
            0xff, 0xff
    };
    const unsigned char output[] = {
            0x3f, 0xff, 0xfc, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs1)
{
    const unsigned char input[] = {
            0xff
    };
    const unsigned char output[] = {
            0x77, 0x78, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs_decode_4)
{
    const unsigned char output[] = {
            0xff, 0xff, 0xff, 0xff
    };
    const unsigned char input[] = {
            0x17, 0xff, 0xff, 0xff, 0x7e,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs_decode_3)
{
    const unsigned char output[] = {
            0xff, 0xff, 0xff, 0x00
    };
    const unsigned char input[] = {
            0x3f, 0xff, 0xff, 0xfc, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs_decode_2)
{
    const unsigned char output[] = {
            0xff, 0xff, 0x00, 0x00
    };
    const unsigned char input[] = {
            0x3f, 0xff, 0xfc, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(fs_decode_1)
{
    const unsigned char output[] = {
            0xff, 0x00, 0x00, 0x00
    };
    const unsigned char input[] = {
            0x77, 0x78, 0x00, 0x00, 0x00,
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(encode_first_five)
{
    const unsigned char input[] = {
            0x00, 0x01, 0x02, 0x03, 0x04
    };
    const unsigned char output[] = {
            0x20, 0x80, 0x04, 0x08, 0x06, 0x20, 0xa0, 0x00,  0x00, 0x00
    };

    INPUT_BYTES(input);
    CHECK(app_main("-e") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(decode_first_four)
{
    const unsigned char output[] = {
            0x00, 0x01, 0x02, 0x03
    };
    const unsigned char input[] = {
            0x20, 0x80, 0x04, 0x08, 0x06
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(decode_first_four_faulty)
{
    const unsigned char output[] = {
            0x00, 0x01, 0x02, 0x03
    };
    const unsigned char input[] = {
            0x30, 0x80, 0x04, 0x08, 0x06
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_SUCCESS);
    CHECK_FILE(stderr, "One-bit error in byte 0\n");
    CHECK_BINARY_FILE(stdout, output);
}

TEST(decode_one_on_end)
{
    const unsigned char input[] = {
            0x00, 0x00, 0x00, 0x00, 0x01
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_FAILURE);
    CHECK_FILE(stderr, "");
}

TEST(decode_one_on_start)
{
    const unsigned char input[] = {
            0x80, 0x00, 0x00, 0x00, 0x00
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_FAILURE);
    CHECK_FILE(stderr, "");
}

TEST(decode_wrong_word)
{
    const unsigned char input[] = {
            0x00, 0x00, 0x00, 0x00
    };

    INPUT_BYTES(input);
    CHECK(app_main("-d") == EXIT_FAILURE);
    CHECK_FILE(stderr, "Wrong code word\n");
}