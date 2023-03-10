#include <stdio.h>
#include <stdlib.h>

#define UNUSED(A) (void) (A)
#define BOARD_SIZE 20
#define STRING_SIZE 32

#define NOBODY_WON 0
#define XS_WON 1
#define OS_WON 2
#define DRAW 3

#define GAMEPLAY_OK 0
#define GAMEPLAY_ERROR 1

#define EMPTY_CHAR ' '

/**
 * Prints border between the lines of gameboard
 */
static void print_border(void);

/**
 *  Prints one line of game
 *
 *  @param i number of line within gameboard
 *  @param line one line of gameboard
 */
static void print_game_line(size_t i, char line[BOARD_SIZE]);

/**
 * Prints whole gameboard
 *
 * @param board the board to be printed
 */
static void print_game_board(char board[BOARD_SIZE][BOARD_SIZE]);

/**
 *  Function to initialize game board
 *
 *  @param board game board to be initialized
 *  @param init_value default value of the elements within the board
 */
void init_game_board(char board[BOARD_SIZE][BOARD_SIZE], char init_value);

/**
 * Function to process single input into the game, store it and signalize
 * error state if input is invalid
 *
 * @param board place where the game move is to be stored
 * @param iteration zero-based iteration of the game
 * @param player_names names of the players
 *
 * @return GAMEPLAY_OK if one turn has ended, GAMEPLAY_ERROR is returned, when
 * unrecorevable error is found (e.g. closed input)
 */
int play_turn(char board[BOARD_SIZE][BOARD_SIZE], short iteration, char player_names[2][STRING_SIZE]);

/**
 * Function checks if the game board contains winning line.
 * Winning line is defined as sequence of same character of length 5
 * in same row, column or diagonal.
 *
 * @param board the game board to be checked
 *
 * @return NOBODY_WON when there is no winning sequence on the game board, {XS,OS}_WON when
 * x player or o player won and DRAW when there is no free place on the gameboard to be filled
 */
int check_winning_move(char board[BOARD_SIZE][BOARD_SIZE]);

int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE] = { { 0 } };
    char player_names[2][STRING_SIZE] = { { '\0' }, { '\0' } };
    init_game_board(board, EMPTY_CHAR);

    printf("Enter name of first player (x): ");

    if (scanf(" %31s", player_names[0]) != 1) {
        printf("Invalid input for name!\n");
        return EXIT_FAILURE;
    }

    printf("Enter name of second player (o): ");
    if (scanf(" %31s", player_names[1]) != 1) {
        printf("Invalid input for name!\n");
        return EXIT_FAILURE;
    }

    print_game_board(board);

    int game_end = NOBODY_WON;
    short iteration = 0;

    while (game_end == NOBODY_WON) {
        if (play_turn(board, iteration, player_names)) {
            printf("Unrecorevable error happened. Ending the game....\n");
            return EXIT_FAILURE;
        }

        game_end = check_winning_move(board);
        iteration++;
    }

    if (game_end == DRAW) {
        printf("Nobody won, game is draw.\n");
    } else {
        printf("%s won the game\n", (game_end == XS_WON) ? player_names[0] : player_names[1]);
    }

    return 0;
}

int play_turn(char board[BOARD_SIZE][BOARD_SIZE], short iteration, char player_names[2][STRING_SIZE])
{
    printf("%s: ", player_names[iteration % 2]);
    int row = -1;
    int column = -1;
    int status = scanf(" %d %d", &row,&column);
    if (status == EOF || column < 0 || row < 0 || board[row][column] != EMPTY_CHAR)
    {
        return GAMEPLAY_ERROR;
    }
    board[row][column] = iteration % 2 == 0 ? 'X' : 'O';
    UNUSED(iteration);
    UNUSED(player_names);
    print_game_board(board);

    return GAMEPLAY_OK;
}

int check_winning_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int empty_spaces = 0;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int column = 0; column < BOARD_SIZE; column++)
        {
            char curr_char = board[row][column];
            if (curr_char == EMPTY_CHAR)
            {
                empty_spaces += 1;
                continue;
            }

            // to the right
            for (short shift = 1; shift < 5; shift++)
            {
                if (column + shift > BOARD_SIZE - 1 || board[row][column + shift] != curr_char)
                {
                    break;
                }
                if (shift == 4)
                {
                    return curr_char == 'X' ? XS_WON : OS_WON;
                }
            }

            // down
            for (short shift = 1; shift < 5; shift++)
            {
                if (row + shift > BOARD_SIZE - 1 || board[row + shift][column] != curr_char)
                {
                    break;
                }
                if (shift == 4)
                {
                    return curr_char == 'X' ? XS_WON : OS_WON;
                }
            }

            // diagonally to the right
            for (short shift = 1; shift < 5; shift++)
            {
                if (column + shift > BOARD_SIZE - 1
                || row + shift > BOARD_SIZE - 1
                || board[row + shift][column + shift] != curr_char)
                {
                    break;
                }
                if (shift == 4)
                {
                    return curr_char == 'X' ? XS_WON : OS_WON;
                }
            }

            // diagonally to the left
            for (short shift = 1; shift < 5; shift++)
            {
                if (row + shift > BOARD_SIZE - 1
                    || column - shift < 0
                    || board[row + shift][column - shift] != curr_char)
                {
                    break;
                }
                if (shift == 4)
                {
                    return curr_char == 'X' ? XS_WON : OS_WON;
                }
            }
        }
    }
    if (empty_spaces == 0)
    {
        return DRAW;
    }
    return NOBODY_WON;
    UNUSED(board);
}

void print_game_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    printf("    ");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf(" %2d ", (int) i);
    }
    printf("\n");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        print_border();
        print_game_line(i, board[i]);
    }
    print_border();
}

static void print_border(void)
{
    printf("   +");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf("---+");
    }
    printf("\n");
}

static void print_game_line(size_t line_no, char line[BOARD_SIZE])
{
    printf("%2d |", (int) line_no);
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf(" %c |", line[i]);
    }
    printf("\n");
}

void init_game_board(char board[BOARD_SIZE][BOARD_SIZE], char init_value)
{
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = init_value;
        }
    }
}
