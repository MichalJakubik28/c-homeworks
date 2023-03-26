#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFO_WORD_OK 0
#define END_OF_STREAM 1
#define INFO_WORD_ERROR 2
#define INFO_WORD_SIZE 4
#define CODEWORD_SIZE 5
#define INFO_WORD_BIT_SIZE (INFO_WORD_SIZE * 8)
#define CODEWORD_BIT_SIZE (CODEWORD_SIZE * 8)

void print_output_bytes(unsigned int length, const unsigned long *word)
{
    unsigned char output_byte = 0;
    for (unsigned int i = length * 8; i >= 8; i -= 8) {
        output_byte = 0;
        output_byte = output_byte | (*word >> (i - 8));
        putchar(output_byte);
    }
}

bool read_info_word(unsigned int *info_word)
{
    unsigned int available_bytes = 0;
    int curr_byte = 0;

    // load 4 bytes
    while (available_bytes < INFO_WORD_SIZE) {
        curr_byte = getchar();
        if (curr_byte == EOF) {
            if (available_bytes == 0) {
                return false;
            }
            break;
        }

        // add byte to info_word
        *info_word = *info_word << 8;
        *info_word = *info_word | curr_byte;
        available_bytes += 1;
    }

    // set 0 to leftover bits if byte amount not divisible by 4
    *info_word = *info_word << ((INFO_WORD_SIZE - available_bytes) * 8);
    return true;
}

unsigned long info_word_to_codeword(unsigned int info_word)
{
    unsigned long codeword = 0;
    int nearest_two_power = 4;

    for (int curr_code_bit = 3; curr_code_bit < CODEWORD_BIT_SIZE; curr_code_bit++) {
        codeword = codeword << 1;
        if (curr_code_bit == nearest_two_power) {
            nearest_two_power = nearest_two_power << 1;
            continue;
        }

        // add current info bit to codeword
        codeword = codeword | ((info_word & 0x80000000) >> (INFO_WORD_BIT_SIZE - 1));
        info_word = info_word << 1;
    }

    return codeword;
}

unsigned long set_parity_bits(unsigned long codeword)
{
    unsigned int parity = 0;

    // set parity bit for each position that is a power of 2
    for (unsigned int power = 1; power <= 32; power = power << 1) {
        parity = 0;
        for (unsigned int curr_bit = power; curr_bit < CODEWORD_BIT_SIZE; curr_bit++) {
            // bit has current power in its position number
            if ((curr_bit & power) != 0) {
                // "xor" parity bit with current bit (shift codeword so that current bit is the least significant and
                // then "and" it with 1 to check its value)
                parity = parity ^ ((codeword >> (CODEWORD_BIT_SIZE - 1 - curr_bit)) & 1);
            }
        }
        if (parity == 1) {
            // set parity bit by "or-ing" it with 1 shifted by the power's position
            codeword = codeword | (1l << (CODEWORD_BIT_SIZE - 1 - power));
        }
    }

    return codeword;
}

bool encode(void)
{
    while (1) {
        unsigned int info_word = 0;
        if (!read_info_word(&info_word)) {
            return true;
        }

        unsigned long codeword = info_word_to_codeword(info_word);

        codeword = set_parity_bits(codeword);

        // print 5 bytes of codeword
        print_output_bytes(CODEWORD_SIZE, &codeword);
    }
}

int read_codeword(unsigned long *codeword)
{
    unsigned int available_bytes = 0;
    int curr_byte = 0;

    while (available_bytes < CODEWORD_SIZE) {
        curr_byte = getchar();
        if (curr_byte == EOF) {
            if (available_bytes == 0) {
                return END_OF_STREAM;
            }

            return INFO_WORD_ERROR;
        }

        available_bytes += 1;

        // words with first or last bit set to 1 are invalid
        if ((available_bytes == 1 && (curr_byte & 0x80) != 0) || (available_bytes == CODEWORD_SIZE && (curr_byte & 0x01) != 0)) {
            return INFO_WORD_ERROR;
        }

        // add byte to codeword
        *codeword = *codeword << 8;
        *codeword = *codeword | curr_byte;
    }
    return INFO_WORD_OK;
}

unsigned long correct_codeword(unsigned long codeword, unsigned long long processed)
{
    unsigned char faulty_bit = 0;

    // compute xor of all positions set to 1
    for (int i = CODEWORD_BIT_SIZE - 1; i > 0; i--) {
        if (((codeword >> i) & 1) == 1) {
            faulty_bit = faulty_bit ^ (CODEWORD_BIT_SIZE - 1 - i);
        }
    }

    if (faulty_bit != 0) {
        fprintf(stderr, "One-bit error in byte %llu\n", faulty_bit / 8 + processed);

        // switch faulty bit by "xor-ing" it with 1 shifted by the faulty bit's position
        return codeword ^ (1l << (CODEWORD_BIT_SIZE - 1 - faulty_bit));
    }

    return codeword;
}

unsigned long codeword_to_info_word(unsigned long codeword)
{
    unsigned int info_word = 0;
    int nearest_two_power = 1;
    for (int i = CODEWORD_BIT_SIZE - 1; i > 0; i--) {
        // skip powers of 2
        if (CODEWORD_BIT_SIZE - 1 - i == nearest_two_power) {
            nearest_two_power = nearest_two_power << 1;
            continue;
        }

        // add current bit by "or-ing" it with info_word
        info_word = info_word << 1;
        info_word = info_word | ((codeword >> i) & 1);
    }

    return info_word;
}

bool decode(void)
{
    unsigned long long processed_bytes = 0;
    while (1) {
        unsigned long codeword = 0;

        switch (read_codeword(&codeword)) {
        case END_OF_STREAM:
            return true;
        case INFO_WORD_ERROR: {
            fprintf(stderr, "Wrong code word\n");
            return false;
        }
        default:
            break;
        }

        codeword = correct_codeword(codeword, processed_bytes);

        unsigned int info_word = codeword_to_info_word(codeword);

        // print 4 bytes of information word
        print_output_bytes(INFO_WORD_SIZE, (unsigned long *) &info_word);

        processed_bytes += CODEWORD_SIZE;
    }
}

/*************************************
 * DO NOT MODIFY THE FUNCTION BELLOW *
 *************************************/
int main(int argc, char *argv[])
{
    if (argc > 2) {
        fprintf(stderr, "Usage: %s (-e|-d)\n", argv[0]);
        return EXIT_FAILURE;
    }
    bool is_success = false;
    if (argc == 1 || (strcmp(argv[1], "-e") == 0)) {
        is_success = encode();
    } else if (strcmp(argv[1], "-d") == 0) {
        is_success = decode();
    } else {
        fprintf(stderr, "Unknown argument: %s\n", argv[1]);
    }
    return is_success ? EXIT_SUCCESS : EXIT_FAILURE;
}
