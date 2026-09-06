#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gol.h"

// Define ANSI color codes
const char* RESET = "\x1b[0m";
const char* GREEN = "\x1b[32m";
const char* GREY  = "\x1b[90m";

// Define the block character (using Unicode here)
const char* BLOCK = "\u2588";

/* Starts the game with "num" cells alive
   placed in random positions */
void start_game(int** current_gen, int num, int wid, int len) {
    int x, y;
   
    srand(clock());
    for (int i = 0; i < num; i++) {
        y = rand() % wid;
        x = rand() % len;
        
        current_gen[y][x] = 1;
    }
}

/* Generates the next generation */ 
void get_next_gen(int **current_gen,  int **next_gen, int wid, int len) {
    for (int i = 0; i < wid; i++)
        for (int j = 0; j < len; j++)
            next_gen[i][j] = next_state(i, j, current_gen, wid, len);

    for (int i = 0; i < wid; i++)
        for (int j = 0; j < len; j++)
            current_gen[i][j] = next_gen[i][j];
}

/* Calculate the next state of the cell */
int next_state(int y, int x, int** world, int wid, int len) {
    int cell  = world[y][x];
    int state = 0;
    int dx, dy;

    for (int i = -1; i <= 1; i++) {
        dy = y + i;
        for (int j = -1; j <= 1; j++) {
            dx = x + j;

            if (dx >= 0 && dy >= 0 && dx < len && dy < wid)
                state += world[dy][dx];
        }
    }

    state -= cell;

    if (cell && (state < 2 || state > 3))
        return 0;
    else if (cell && (state == 2 || state == 3))
        return 1;
    else if (!cell && state == 3)
        return 1;
    else
        return cell;
}

void print_gen(int** gen, int wid, int len) {
    int dx = (LENGTH - len) / 2;
    int dy = (WIDTH  - wid) / 2;

    printf("\033[1;1H\033[?25l");
    
    printf("\n\n\n");
    for (int i = dy; i < wid + dy; i++) {
        printf("\t");
        for (int j = dx; j < len + dx; j++) {
            if (gen[i][j] == 0)
                printf("%s%s%s ", GREY, BLOCK, RESET);
            else
                printf("%s%s%s ", GREEN, BLOCK, RESET);

        }

        printf("\n");
    }
    printf("\n");
}

/* Checks equality between two generations */
int equal(int** gen1, int** gen2, int wid, int len) {
    for (int i = 0; i < wid; i++)
        for (int j = 0; j < len; j++)
            if (gen1[i][j] != gen2[i][j])
                return 0;
    return 1;
}

void free_gen(int** gen, int wid) {
    for (int i = 0; i < wid; i++)
        free(gen[i]);
    free(gen);
}
