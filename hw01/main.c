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
    unsigned char out_byte = 0;
    for (unsigned int i = length * 8; i >= 8; i -= 8) {
        out_byte = 0;
        out_byte = out_byte | (*word >> (i - 8));
        putchar(out_byte);
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
        *info_word = *info_word << 8;
        *info_word = *info_word | curr_byte;
        available_bytes += 1;
    }

    // set 0 to leftover bits if byte amount not divisible by 4
    *info_word = *info_word << ((INFO_WORD_SIZE - available_bytes) * 8);
    return true;
}

unsigned long set_parity_bits(unsigned long codeword)
{
    unsigned int parity = 0;

    // set parity bit for each position that is a power of 2
    for (unsigned int power = 1; power <= 32; power = power << 1) {
        parity = 0;
        for (unsigned int index = power; index < CODEWORD_BIT_SIZE; index++) {
            if ((index & power) != 0) {
                parity = parity ^ ((codeword >> (CODEWORD_BIT_SIZE - 1 - index)) & 1);
            }
        }
        if (parity == 1) {
            codeword = codeword | (1l << (CODEWORD_BIT_SIZE - 1 - power));
        }
    }

    return codeword;
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
        codeword = codeword | ((info_word & 0x80000000) >> (INFO_WORD_BIT_SIZE - 1));
        info_word = info_word << 1;
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

        if ((available_bytes == 1 && (curr_byte & 0x80) != 0) || (available_bytes == CODEWORD_SIZE && (curr_byte & 0x01) != 0)) {
            return INFO_WORD_ERROR;
        }
        *codeword = *codeword << 8;
        *codeword = *codeword | curr_byte;
    }
    return INFO_WORD_OK;
}

unsigned long correct_codeword(unsigned long codeword, unsigned long long processed)
{
    unsigned char correction_xor = 0;

    // compute xor of all positions set to 1
    for (int i = CODEWORD_BIT_SIZE - 1; i > 0; i--) {
        if (((codeword >> i) & 1) == 1) {
            correction_xor = correction_xor ^ (CODEWORD_BIT_SIZE - 1 - i);
        }
    }

    if (correction_xor != 0) {
        fprintf(stderr, "One-bit error in byte %llu\n", correction_xor / 8 + processed);
        return codeword ^ (1l << (CODEWORD_BIT_SIZE - 1 - correction_xor));
    }

    return codeword;
}

unsigned long codeword_to_info_word(unsigned long codeword)
{
    unsigned int info_word = 0;
    int nearest_two_power = 1;
    for (int i = CODEWORD_BIT_SIZE - 1; i > 0; i--) {
        if (CODEWORD_BIT_SIZE - 1 - i == nearest_two_power) {
            nearest_two_power = nearest_two_power << 1;
            continue;
        }
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
