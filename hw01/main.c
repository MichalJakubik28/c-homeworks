#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool encode(void)
{
    int scanned = 1;

    while (1) {
        unsigned char byte1, byte2, byte3, byte4;
        scanned = scanf("%c%c%c%c", &byte1, &byte2, &byte3, &byte4);

        if (scanned == EOF) {
            break;
        }

        unsigned int info_word = 0;
        info_word = info_word | byte1;
        info_word = info_word << 8;
        info_word = info_word | byte2;
        info_word = info_word << 8;
        info_word = info_word | byte3;
        info_word = info_word << 8;
        info_word = info_word | byte4;

        // set 0 to leftover bits if byte amount not divisible by 4
        info_word = info_word & (0xFFFFFFFF << (4 - scanned) * 8);

        unsigned long codeword = 0;
        int nearest_two_power = 4;

        for (int curr_code_bit = 3; curr_code_bit < 40; curr_code_bit++) {
            codeword = codeword << 1;
            if (curr_code_bit == nearest_two_power) {
                nearest_two_power = nearest_two_power << 1;
                continue;
            }
            codeword = codeword | ((info_word & 0x80000000) >> 31);
            info_word = info_word << 1;
        }

        unsigned int xor = 0;

        for (unsigned int power = 1; power <= 32; power = power << 1) { // for each power
            xor = 0;
            for (unsigned int index = power; index < 40; index++) {
                if ((index & power) != 0) {
                    xor = xor^((codeword >> (39 - index)) & 1);
                }
            }
            if (xor == 1) {
                codeword = codeword | (1l << (39 - power));
            }
        }

        unsigned char out_byte = 0;
        for (int i = 32; i >= 0; i -= 8) {
            out_byte = 0;
            out_byte = out_byte | (codeword >> i);
            putchar(out_byte);
        }
    }
    return true;
}

bool decode(void)
{
    int scanned = 1;
    unsigned int processed_bytes = 0;

    while (1) {
        unsigned char byte1, byte2, byte3, byte4, byte5;
        scanned = scanf("%c%c%c%c%c", &byte1, &byte2, &byte3, &byte4, &byte5);

        if (scanned == EOF) {
            break;
        }

        if (scanned != 5) {
            fprintf(stderr, "Wrong code word\n");
            return false;
        }

        if ((byte1 & 0x80) != 0 || (byte5 & 0x01) != 0) {
            fprintf(stderr, "Wrong code word\n");
            return false;
        }


        unsigned long code_word = 0;
        code_word = code_word | byte1;
        code_word = code_word << 8;
        code_word = code_word | byte2;
        code_word = code_word << 8;
        code_word = code_word | byte3;
        code_word = code_word << 8;
        code_word = code_word | byte4;
        code_word = code_word << 8;
        code_word = code_word | byte5;

        unsigned char correction_xor = 0;

        for (int i = 39; i > 0; i--) {
            if (((code_word >> i) & 1) == 1) {
                correction_xor = correction_xor ^ (39 - i);
            }
        }
        if (correction_xor != 0) {
            fprintf(stderr, "One-bit error in byte %d\n", correction_xor / 8 + processed_bytes);
        }
        code_word = code_word ^ (1l << (39 - correction_xor));

        unsigned int info_word = 0;
        int nearest_two_power = 1;
        for (int i = 39; i > 0; i--) {
            if (39 - i == nearest_two_power) {
                nearest_two_power = nearest_two_power << 1;
                continue;
            }
            info_word = info_word << 1;
            info_word = info_word | ((code_word >> i) & 1);
        }

        unsigned char out_byte = 0;
        for (int i = 24; i >= 0; i -= 8) {
            out_byte = 0;
            out_byte = out_byte | (info_word >> i);
            putchar(out_byte);
        }

        processed_bytes += 5;
    }

    return true;
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
