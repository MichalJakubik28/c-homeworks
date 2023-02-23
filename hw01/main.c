#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool encode(void)
{
    // TODO implement
    int scanned = 1;
    while (scanned > 0) {
      char bytes[4];
      scanned = scanf( "%c%c%c%c", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
      if (scanned == EOF) {
        return true;
      }
      printf("scanned: %d \n", scanned);
      for (int i = scanned; i < 4; i++) {
        bytes[i] = 0;
      }
      for (int i = 0; i < 4; i++) {
        printf("%d ", bytes[i]);
      }
      putchar('\n');

      int info_word = 0;
      for (int i = 0; i < 4; i++) {
        info_word = info_word << 8;
        info_word = info_word | bytes[i];
      }
      printf("Number: %d \n", info_word);
      /*char codeword[5] = {0, 0, 0, 0, 0};
      int curr_index = 3;
      int curr_bit = 0;
      char mask = 0;
      int nearest_two_power = 4;
      while (curr_index < 39) {
          if (nearest_two_power == curr_index) {
              nearest_two_power = nearest_two_power << 1;
              curr_index += 1;
              continue;
          }
          curr_index += 1;
      }*/


    }
    return true;
}

bool decode(void)
{
    // TODO implement
    return false;
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
