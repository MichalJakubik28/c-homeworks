#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALL_PLAYERS (-1)
#define CARDS_OK 0
#define CARDS_ERROR 1
#define NO_CARDS 2

char convert_and_store(char value, char color, int players, int player_number, bool cards[players][13][4]);
int read_input_cards(int players, bool cards[players][13][4]);
void find_best_combination(char best_cards[6], const bool player_cards[13][4]);
void straight_flush(char best_cards[6], const bool cards[13][4]);
void four_of_a_kind(char best_cards[6], const bool cards[13][4]);
void full_house(char best_cards[6], const bool cards[13][4]);
void flush(char best_cards[6], const bool cards[13][4]);
void straight(char best_cards[6], const bool cards[13][4]);
void three_of_a_kind(char best_cards[6], const bool cards[13][4]);
void two_pair(char best_cards[6], const bool cards[13][4]);
void pair(char best_cards[6], const bool cards[13][4]);
int compare_players(int former_best, int competitor, int players, const char best_cards[players][6], bool *draw);
char n_of_a_kind(const bool cards[13][4], int n, char forbidden);
void fill_with_highest(char best_cards[6], const bool cards[13][4], int forbidden, int empty_amount);
bool find_and_assign_noak(const bool cards[13][4], char best_cards[6], int start_index, int card_amount, char forbidden);
int mod(int a, int b);

/* Parse the number of players at the table for the bonus extension.
 * IMPORTANT: Do not modify this function! */
static int parse_players(int argc, char **argv)
{
    switch (argc) {
    case 1:
        return 2;
    case 2:
        return atoi(argv[1]);
    default:
        return 0;
    }
}

int main(int argc, char **argv)
{
    int players = parse_players(argc, argv);

    if (players <= 1 || players > 8) {
        fprintf(stderr, "Invalid number of players\n");
        return 1;
    }

    while (true) {
        // cards: players * value * color
        bool cards[players][13][4];
        memset(cards, false, players * 13 * 4);

        switch (read_input_cards(players, cards)) {
        case NO_CARDS:
            return 0;
        case CARDS_ERROR:
            return 1;
        default:
            break;
        }

        // array of combination rank and 5 strongest cards for each player
        char best_combinations[players][6];
        memset(best_combinations, -1, players * 6);

        // find the best combination for all players
        for (int i = 0; i < players; i++) {
            find_best_combination(best_combinations[i], (const bool(*)[4]) cards[i]);
        }

        // compare players
        int best_player = 0;
        bool draw = false;
        for (int competitor = 1; competitor < players; competitor++) {
            best_player = compare_players(best_player, competitor, players, (const char(*)[6]) best_combinations, &draw);
        }
        if (draw) {
            printf("Draw\n");
            continue;
        }
        printf("Player %d\n", best_player + 1);
    }
}

/* Compares best cards of two players and returns the number of the winner, sets */
int compare_players(const int former_best, const int competitor, const int players, const char best_cards[players][6], bool *draw)
{
    for (int i = 0; i < 6; i++) {
        if (best_cards[former_best][i] != best_cards[competitor][i]) {
            if (best_cards[former_best][i] > best_cards[competitor][i]) {
                return former_best;
            }
            *draw = false;
            return competitor;
        }
    }

    *draw = true;
    return competitor;
}

void find_best_combination(char best_cards[6], const bool player_cards[13][4])
{
    void (*check_combination[])(char[], const bool[13][4]) = { &pair, &two_pair, &three_of_a_kind, &straight, &flush, &full_house, &four_of_a_kind, &straight_flush };
    for (int i = 7; i >= 0; i--) {
        check_combination[i](best_cards, player_cards);
        if (best_cards[5] != -1) {
            best_cards[0] = (char) (i + 1);
            return;
        }
        memset(best_cards, -1, 6);
    }

    // no combination found, fill with the highest cards
    fill_with_highest(best_cards, player_cards, -1, 5);
    best_cards[0] = '\0';
}

int read_player_cards(int player_number, char *card_value, char *card_color, int players, bool cards[players][13][4])
{
    for (int j = 0; j < 2; j++) {
        int scanned = scanf(" %c%c", card_value, card_color);
        if (scanned == EOF && player_number == 0 && j == 0) {
            return NO_CARDS;
        }
        if (scanned != 2) {
            fprintf(stderr, "Error reading card %d of player %d\n", j + 1, player_number + 1);
            return CARDS_ERROR;
        }
        if (j == 0) {
            int whitespaces = 0;
            scanf(" %n", &whitespaces);
            if (whitespaces == 0) {
                fprintf(stderr, "No whitespace after first card of player %d\n", player_number + 1);
                return CARDS_ERROR;
            }
        }
        // value and color conversion
        if (convert_and_store(*card_value, *card_color, players, player_number, cards) == CARDS_ERROR) {
            return CARDS_ERROR;
        }
    }
    int newline = getchar();
    if (newline != '\n') {
        fprintf(stderr, "Wrong separator of player %d\n", player_number + 1);
        return CARDS_ERROR;
    }
    return CARDS_OK;
}

int read_table_cards(char card_value, char card_color, int players, bool cards[players][13][4])
{
    for (int i = 0; i < 5; i++) {
        int scanned = scanf(" %c%c", &card_value, &card_color);
        if (scanned != 2) {
            fprintf(stderr, "Error reading table card %d\n", i + 1);
            return CARDS_ERROR;
        }
        if (i != 4) {
            int whitespaces = 0;
            scanf(" %n", &whitespaces);
            if (whitespaces == 0) {
                fprintf(stderr, "No whitespace after table card %d\n", i + 1);
                return CARDS_ERROR;
            }
        }
        // value and color conversion
        if (convert_and_store(card_value, card_color, players, ALL_PLAYERS, cards) == CARDS_ERROR) {
            return CARDS_ERROR;
        }
    }
    int newline = getchar();
    if (newline != '\n') {
        fprintf(stderr, "Wrong separator at end of table cards\n");
        return CARDS_ERROR;
    }
    return CARDS_OK;
}

int read_input_cards(const int players, bool cards[players][13][4])
{
    char card_value = 0;
    char card_color = 0;

    for (int i = 0; i < players; i++) {
        int card_status = read_player_cards(i, &card_value, &card_color, players, cards);
        if (card_status != CARDS_OK) {
            return card_status;
        }
    }

    int table_status = read_table_cards(card_value, card_color, players, cards);
    if (table_status != CARDS_OK) {
        return table_status;
    }

    return CARDS_OK;
}

int convert_value(int value)
{
    int value_index = -1;

    switch (value) {
    case 'A':
        value_index = 12;
        break;
    case 'K':
        value_index = 11;
        break;
    case 'Q':
        value_index = 10;
        break;
    case 'J':
        value_index = 9;
        break;
    case 'T':
        value_index = 8;
        break;
    default:
        break;
    }

    // convert ascii numbers to indices 0-7
    if (value >= '2' && value <= '9') {
        value_index = value - 50;
    }

    return value_index;
}

int convert_color(int color)
{
    int color_index = -1;
    switch (color) {
    case 'c':
        color_index = 3;
        break;
    case 's':
        color_index = 2;
        break;
    case 'd':
        color_index = 1;
        break;
    case 'h':
        color_index = 0;
        break;
    default:
        break;
    }

    return color_index;
}

/* Converts input to card and stores it */
char convert_and_store(const char value, const char color, const int players, const int player_number, bool cards[players][13][4])
{
    if (players > 8 || players <= 1) {
        return CARDS_ERROR;
    }

    int value_index = convert_value(value);
    int color_index = convert_color(color);

    if (value_index == -1 || color_index == -1 || player_number > players - 1) {
        fprintf(stderr, "Invalid index or player number\n");
        return CARDS_ERROR;
    }

    for (int i = 0; i < players; i++) {
        bool card = cards[i][value_index][color_index];
        if (card) {
            fprintf(stderr, "Duplicate cards detected\n");
            return CARDS_ERROR;
        }
    }

    if (player_number == ALL_PLAYERS) {
        for (int i = 0; i < players; i++) {
            cards[i][value_index][color_index] = true;
        }
        return CARDS_OK;
    }

    cards[player_number][value_index][color_index] = true;
    return CARDS_OK;
}

void assign_straight_flush(char best_cards[6], int value, int order)
{
    // case of steel wheel
    if (mod((value - order), 13) == 12) {
        for (int i = 1; i < 6; i++) {
            best_cards[i] = (char) mod(4 - i, 13);
        }
        return;
    }

    for (int i = 5; i > 0; i--) {
        best_cards[6 - i] = (char) (value - order + i - 1);
    }
}

bool found_straight_flush(const bool cards[13][4], int value, int color, char best_cards[6])
{
    for (char order = 0; order <= 4; order++) {
        if (!cards[mod((value - order), 13)][color]) {
            break;
        }

        if (order == 4 && cards[mod((value - order), 13)][color]) {
            assign_straight_flush(best_cards, value, order);
            return true;
        }
    }
    return false;
}

void straight_flush(char best_cards[6], const bool cards[13][4])
{
    for (int color = 0; color < 4; color++) {
        for (char value = 12; value >= 3; value--) {
            if (found_straight_flush(cards, value, color, best_cards)) {
                return;
            }
        }
    }
}

void four_of_a_kind(char best_cards[6], const bool cards[13][4])
{
    if (!find_and_assign_noak(cards, best_cards, 1, 4, -1)) {
        return;
    }

    fill_with_highest(best_cards, cards, best_cards[1], 1);
}

void full_house(char best_cards[6], const bool cards[13][4])
{
    if (!find_and_assign_noak(cards, best_cards, 1, 3, -1)) {
        return;
    }
    if (!find_and_assign_noak(cards, best_cards, 4, 2, best_cards[1])) {
        return;
    }
}

void flush(char best_cards[6], const bool cards[13][4])
{
    int filled = 0;
    int candidate[5] = { -1, -1, -1, -1, -1 };

    for (int color = 0; color < 4; color++) {
        for (int value = 12; value >= 0; value--) {
            if (filled == 5) {
                break;
            }
            if (cards[value][color]) {
                candidate[filled] = value;
                filled++;
            }
        }
        if (filled == 5) {
            for (int i = 1; i < 6; i++) {
                best_cards[i] = (char) candidate[i - 1];
            }
        }
        filled = 0;
    }
}

/* Finds n of the same and also highest cards, omitting the forbidden value */
char n_of_a_kind(const bool cards[13][4], const int n, const char forbidden)
{
    int same_count = 0;
    for (int value = 12; value >= 0; value--) {
        if (value == forbidden) {
            continue;
        }
        for (int color = 0; color < 4; color++) {
            if (cards[value][color]) {
                same_count++;
            }
            if (same_count == n) {
                return (char) value;
            }
        }
        same_count = 0;
    }

    return -1;
}

void assign_straight(char best_cards[6], int value)
{
    // case of baby straight
    if (mod((value - 4), 13) == 12) {
        for (int i = 1; i < 6; i++) {
            best_cards[i] = (char) (mod(4 - i, 13));
        }
        return;
    }

    for (int i = 5; i > 0; i--) {
        best_cards[6 - i] = (char) (value - 5 + i);
    }
}

bool value_in_cards(const bool cards[13][4], int value, int order)
{
    for (int color = 0; color < 4; color++) {
        if (cards[mod((value - order), 13)][color]) {
            return true;
        }
    }

    return false;
}

void straight(char best_cards[6], const bool cards[13][4])
{
    int consecutive = 0;
    for (char value = 12; value >= 3; value--) {
        for (char order = 0; order <= 4; order++) {
            if (value_in_cards(cards, value, order)) {
                consecutive++;
            }

            // cards are not consecutive
            if (consecutive != order + 1) {
                break;
            }
        }

        if (consecutive == 5) {
            assign_straight(best_cards, value);
            return;
        }
        consecutive = 0;
    }
}

void three_of_a_kind(char best_cards[6], const bool cards[13][4])
{
    if (!find_and_assign_noak(cards, best_cards, 1, 3, -1)) {
        return;
    }
    for (int i = 1; i < 4; i++) {
        best_cards[i] = best_cards[1];
    }
    fill_with_highest(best_cards, cards, best_cards[1], 2);
}

/* Fills the best_cards array with highest cards of the player */
void fill_with_highest(char best_cards[6], const bool cards[13][4], const int forbidden, const int empty_amount)
{
    char filled = 0;
    for (int value = 12; value >= 0; value--) {
        for (int color = 0; color < 4; color++) {
            if (cards[value][color] && value != forbidden) {
                best_cards[filled + (6 - empty_amount)] = (char) value;
                filled++;
                if (filled == empty_amount) {
                    return;
                }
                break;
            }
        }
    }
}

void two_pair(char best_cards[6], const bool cards[13][4])
{
    if (!find_and_assign_noak(cards, best_cards, 1, 2, -1)) {
        return;
    }

    if (!find_and_assign_noak(cards, best_cards, 3, 2, best_cards[1])) {
        return;
    }

    // find the largest of the remaining cards
    for (int value = 12; value >= 0; value--) {
        for (int color = 0; color < 4; color++) {
            if (cards[value][color] && value != best_cards[1] && value != best_cards[3]) {
                best_cards[5] = (char) value;
                return;
            }
        }
    }
}

void pair(char best_cards[6], const bool cards[13][4])
{
    if (!find_and_assign_noak(cards, best_cards, 1, 2, -1)) {
        return;
    }

    fill_with_highest(best_cards, cards, best_cards[1], 3);
}

// modulo of a number because C's '%' operator is a remainder, not modulo
int mod(const int a, const int b)
{
    int result = a % b;
    if (result < 0) {
        result = b + result;
    }
    return result;
}

bool find_and_assign_noak(const bool cards[13][4], char best_cards[6], int start_index, int card_amount, char forbidden)
{
    char tuple = n_of_a_kind(cards, card_amount, forbidden);
    if (tuple == -1) {
        return false;
    }

    for (int i = 0; i < card_amount; i++) {
        best_cards[i + start_index] = tuple;
    }

    return true;
}
