#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "gol.h"

/* Prints given options */
void print_options(int count, ...) {
    int i;
    va_list args;
    va_start(args, count);

    for (i = 0; i < count; i++)
        printf("%d) %s\n", i + 1, va_arg(args, char*));

    printf("\nYour Answer: ");
}

/* Prints game grid with numberd labeled cells */
void print_grid(int wid, int len) {
    int ctr = 1;
    printf("\n");
    for (int i = 0; i < wid; i++) {
        for (int j = 0; j < len; j++)
            printf("|%4d    ", ctr++);
        printf("|\n");
    }
    printf("\n");
}

/* Constructs positions from str and  put them in positions array */
int get_positions(char* str, int* positions) {
    char buf[strlen(str)];
    int i, c, state, ctr, pos_ctr;

    i = ctr = pos_ctr = 0;
    state = OUT;
    while((c = str[i++]) != EOF && c != '\0') {
        if (state == OUT && isdigit(c))
            state = IN;
        else if (state == IN  && !isdigit(c)) {
            buf[ctr] = '\0';
            positions[pos_ctr++] = atoi(buf);
            
            ctr   = 0;
            state = OUT;
        }

        if (state == IN)
            buf[ctr++] = c;
    }

    return pos_ctr;
}

/* Makes the cells in posiitons alive */ 
void put_positions(int** gen, int* pos, int pos_num, int wid, int len) {
    int p[pos_num][2];      // p[n][0] -> y position of n && p[n][1] x position of n
    int dx, dy;

    dx = (LENGTH - len) / 2;
    dy = (WIDTH  - wid) / 2;

    for (int i = 0; i < pos_num; i++) {
        pos[i]--;
        p[i][0] = (pos[i] / len ) + dy;
        p[i][1] = (pos[i] % len ) + dx;
    }

    for (int i = 0; i < pos_num; i++)
        gen[p[i][0]][p[i][1]] = 1;
}

/* Put The pattern in the middle of generation grid */
void put_pattern(int** gen, int wid, int len, int pattern[wid][len]) {
    int   dx = (LENGTH - len) / 2;
    int   dy = (WIDTH  - wid) / 2;

    for (int i = 0; i < wid; i++)
        for (int j = 0; j < len; j++) {
            gen[i + dy][j + dx] = pattern[i][j];
        }
}

void clear_screen() {
    printf("\033[2J");
}
