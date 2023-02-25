#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool encode(void) {

    int scanned = 1;

    while (1) {

        unsigned char byte1, byte2, byte3, byte4;
        scanned = scanf("%c%c%c%c", &byte1, &byte2, &byte3, &byte4);

        if (scanned == EOF) {
            break;
        }

        //printf("scanned: %d \n", scanned);

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

        //printf("Number: %d \n", info_word);
        unsigned long codeword = 0;

        int curr_code_bit = 3;
        int nearest_two_power = 4;

        while (curr_code_bit < 40) { // TODO da sa aj do 39
            codeword = codeword << 1;
            if (curr_code_bit == nearest_two_power) {
                curr_code_bit += 1;
                nearest_two_power = nearest_two_power << 1;
                continue;
            }
            codeword = codeword | ((info_word & 0x80000000) >> 31);
            info_word = info_word << 1;
            curr_code_bit += 1;
        }

        /*
        for (int i = 39; i >= 0; i--) {
            printf("%d", ((codeword >> i) & 1) ? 1 : 0);
        }

        putchar('\n');
        */

        unsigned int xor = 0;
        unsigned long one = 1;
        //unsigned long to_and = 0;

        for (unsigned int power = 1; power <= 32; power = power << 1) {    // for each power
            xor = 0;
            for (unsigned int index = power; index < 40; index++) {
                if ((index & power) != 0) {
                    xor = xor ^ ((codeword >> (39 - index)) & 1);
                }
            }
            if (xor == 1) {
                /*
                to_and = one << (39 - power);
                printf("To and with power %d: ", power);
                for (int i = 39; i >= 0; i--) {
                    printf("%d", ((to_and >> i) & 1) ? 1 : 0);
                }
                putchar('\n');
                */

                codeword = codeword | (one << (39 - power));

                /*
                printf("HAPPENED, power: %lu\n", power);
                printf("New number: ");
                for (int i = 39; i >= 0; i--) {
                    printf("%d", ((codeword >> i) & 1) ? 1 : 0);
                }
                putchar('\n');
                */
            }
        }

        /*
        printf("CISLO: dec: %lu hex: %lx\n", codeword, codeword);

        for (int i = 39; i >= 0; i--) {
            printf("%d", ((codeword >> i) & 1) ? 1 : 0);
        }
         */

        unsigned char out_byte = 0;
        for (int i = 32; i >= 0; i -= 8) {
            out_byte = 0;
            out_byte = out_byte | (codeword >> i);
            putchar(out_byte);
        }

    }
    return true;
}

bool decode(void) {
    // TODO implement
    int scanned = 1;

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

        /*
        printf("%lu\n", code_word);
        for (int i = 39; i >= 0; i--) {
            if ((i + 1) % 8 == 0) {
                putchar(32);
            }
            printf("%d", ((code_word >> i) & 1) ? 1 : 0);
        }
         */

        unsigned char correction_xor = 0;
        unsigned long one = 1;
        for (int i = 39; i > 0; i--) {
            if (((code_word >> i) & 1) == 1) {
                correction_xor = correction_xor ^ (39 - i);
            }
        }
        if (correction_xor != 0) {
            fprintf(stderr,"One-bit error in byte %d\n", correction_xor);
        }
        code_word = code_word ^ (one << (39 - correction_xor));


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

        /*
        putchar('\n');
        for (int i = 31; i >= 0; i--) {
            if ((i + 1) % 8 == 0) {
                putchar(32);
            }
            printf("%d", ((info_word >> i) & 1) ? 1 : 0);
        }
         */


        unsigned char out_byte = 0;
        for (int i = 24; i >= 0; i -= 8) {
            out_byte = 0;
            out_byte = out_byte | (info_word >> i);
            putchar(out_byte);
        }
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
