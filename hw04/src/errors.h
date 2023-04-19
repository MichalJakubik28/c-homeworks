#include <setjmp.h>

#ifndef ERRORS_H
#define ERRORS_H

enum error_codes
{
    INITIAL_PASS = 0,
    SUCCESS,

    DUPLICIT_INITIALIZATION,
    ALLOCATION_FAILED,
    CURRENCY_ALREADY_PRESENT,
    CURRENCY_DUPLICATE_MAIN,
    CURRENCY_NOT_FOUND,
    DEFAULT_CURRENCY_NOT_SET,
    NEGATIVE_CURRENCY_RATING,
    PERSON_ALREADY_PRESENT,
    PERSON_NOT_FOUND,
    NOT_ENOUGH_PERSONS,
    INVALID_NUMBER_IN_FILE,
    INVALID_PERSON_ID,
    INVALID_CURRENCY_ID,
    INVALID_AMOUNT,
    INVALID_RATING,
    INVALID_PERSON_NAME,

    INVALID_ARGUMENTS
};

#define stack_top_frame()        \
    jmp_buf current_frame;       \
    enum error_codes frame_code; \
    set_error_point(&current_frame)
#define stack_frame()                                      \
    jmp_buf current_frame, *top_frame = get_error_point(); \
    enum error_codes frame_code;                           \
    set_error_point(&current_frame)
#define read_error_point() (frame_code = (enum error_codes) setjmp(*get_error_point()))
#define leave(value)                                             \
    do {                                                         \
        set_error_point(top_frame);                              \
        if (frame_code == INITIAL_PASS || frame_code == SUCCESS) \
            return value;                                        \
        error_happened(frame_code);                              \
    } while (0)

#define OP(DO, ERR) (void) ((DO) || error_happened(ERR))

void print_error_message(enum error_codes code);
int return_code(enum error_codes code);
void set_error_point(jmp_buf *point);
jmp_buf *get_error_point(void);
int error_happened(enum error_codes code);
void exit_success(void);

#endif
