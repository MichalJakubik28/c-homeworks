#include <stdio.h>

void draw_in_binary(int num, int max_bits)
{
    // compute bit position for comparison
    int comparing_bit = 1 << (max_bits - 1);

    // starting bit-by-bit comparison from most significant bit
    for (int i = 0; i < max_bits; i++) {
        if (num & comparing_bit) {
            putchar('#');
        } else {
            putchar('.');
        }
        num = num << 1;
    }
}

void draw_time(int hours, int minutes)
{
    if (hours < 0 || hours > 23) {
        printf("Invalid hours");
        return;
    }

    if (minutes < 0 || minutes > 59) {
        printf("Invalid minutes");
        return;
    }

    printf("%02d:%02d  ", hours, minutes);

    draw_in_binary(hours, 5);

    printf("  ");

    draw_in_binary(minutes, 6);

    putchar('\n');
}

void draw_line(void)
{
    int length = 0;
    printf("Enter length: ");
    if (scanf("%d", &length) != 1) {
        printf("Invalid input");
        return;
    };
    if (length < 0) {
        return;
    }
    while (length > 0) {
        putchar('#');
        length--;
    }
    putchar('\n');
}

void draw_square(int size)
{
    if (size < 0) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            putchar('#');
            putchar('#');
        }
        putchar('\n');
    }
}

void draw_rectangle(int a, int b, char fill)
{
    if (a < 0 || b < 0) {
        return;
    }

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            putchar(fill);
        }
        putchar('\n');
    }
}

void draw_circle(int radius, char fill, char space)
{
    if (radius < 0) {
        return;
    }

    int x_coord_sq = 0;
    int y_coord_sq = 0;
    int radius_sq = radius * radius;

    for (int i = 0; i < 2 * radius; i++) {
        for (int j = 0; j < 4 * radius; j++) {
            x_coord_sq = ((j - 2 * radius) / 2) * ((j - 2 * radius) / 2);
            y_coord_sq = (i - radius) * (i - radius);
            putchar((x_coord_sq + y_coord_sq) < radius_sq ? fill : space);
        }
        putchar('\n');
    }
}

void draw_ellipse(int a_axis, int b_axis, char fill, char space)
{
    if (a_axis < 0 || b_axis < 0) {
        return;
    }

    int x_coord_sq = 0;
    int y_coord_sq = 0;
    int a_axis_sq = a_axis * a_axis;
    int b_axis_sq = b_axis * b_axis;

    for (int i = 0; i < 2 * b_axis; i++) {
        for (int j = 0; j < 4 * a_axis; j++) {
            x_coord_sq = ((j - 2 * a_axis) / 2) * ((j - 2 * a_axis) / 2);
            y_coord_sq = (i - b_axis) * (i - b_axis);

            // calculate space/fill character without division
            putchar((x_coord_sq * b_axis_sq + y_coord_sq * a_axis_sq < a_axis_sq * b_axis_sq) ? fill : space);
        }
        putchar('\n');
    }
}

int main(void)
{
    // time
    printf("Test of binary time - enter hours, minutes:\n");
    int minutes = 0;
    int hours = 0;
    scanf(" %d", &hours);
    scanf(" %d", &minutes);
    draw_time(hours, minutes);

    // square
    printf("\nTest of square - enter size of the square:\n");
    int size = 0;
    scanf(" %d", &size);
    draw_square(size);

    // rectangle
    printf("\nTest of binary rectangle - enter width, height, fill character:\n");
    int width = 0;
    int height = 0;
    char fill = 0;
    scanf(" %d", &width);
    scanf(" %d", &height);
    scanf(" %c", &fill);
    draw_rectangle(width, height, fill);

    // circle
    printf("\nTest of binary circle - enter radius, fill character, space character:\n");
    int radius = 0;
    char fill2 = 0;
    char space = 0;
    scanf(" %d", &radius);
    scanf(" %c", &fill2);
    scanf(" %c", &space);
    draw_circle(radius, fill2, space);

    // ellipse
    printf("\nTest of binary ellipse - enter a-axis radius, b-axis radius, fill character, space character:\n");
    int a_axis = 0;
    int b_axis = 0;
    char fill3 = 0;
    char space2 = 0;
    scanf(" %d", &a_axis);
    scanf(" %d", &b_axis);
    scanf(" %c", &fill3);
    scanf(" %c", &space2);
    draw_ellipse(a_axis, b_axis, fill3, space2);

    return 0;
}
