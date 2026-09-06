#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "gol.h"
#include "patterns.h"

#define WID(pattern)    \
    sizeof((pattern)) / sizeof((pattern)[0])    \

#define LEN(pattern)    \
    sizeof((pattern)[0]) / sizeof((pattern)[0][0])  \

int main() {
    /* General Variales */   
    int**  current_gen;
    int**  next_gen;
    int choice, pattern_type_choice, pattern_choice;
    
    int    wid, len, delta_t;
    char*  input_buf = NULL;
    size_t input_size = 0;
    int    live_cell_numbers;
    int*   live_cell_positions;

    /* Alocate memory for generation */ 
    current_gen = malloc(WIDTH * sizeof(int*));
    next_gen    = malloc(WIDTH * sizeof(int*));

    for (int i = 0; i < WIDTH; i++) {
        current_gen[i] = malloc(LENGTH * sizeof(int));
        next_gen[i]    = malloc(LENGTH * sizeof(int));
    }

    /* Discover or Build Patterns */
    printf("Welcome to Conway's game of life.\n\n");
    print_options(2, "Discover Patterns", "Build Patterns");
    getline(&input_buf, &input_size, stdin);
    choice = atoi(input_buf);
    printf("\n");
   
    /* Discover Choice */
    if (choice == 1) {
        delta_t = 80;
        printf("Choose The Type of Pattern: \n\n");
        print_options(4, "Still lifes", "Oscillators", "Space Ships", "Guns");
        getline(&input_buf, &input_size, stdin);
        pattern_type_choice = atoi(input_buf);
        printf("\n");

        
        printf("Choose Pattern: \n\n");
        if (pattern_type_choice == 1) {
            print_options(5, "Block", "Bee-hive", "Loaf", "Boat", "Tub");
            getline(&input_buf, &input_size, stdin);
            pattern_choice = atoi(input_buf);

            switch (pattern_choice) {
                case 1:
                    put_pattern(current_gen, WID(block), LEN(block), block);
                    break;

                case 2:
                    put_pattern(current_gen, WID(bee_hive), LEN(bee_hive), bee_hive);
                    break;
                    
                case 3:
                    put_pattern(current_gen, WID(loaf), LEN(loaf), loaf);
                    break;

                case 4:
                    put_pattern(current_gen, WID(boat), LEN(boat), boat);
                    break;

                case 5:
                    put_pattern(current_gen, WID(tub), LEN(tub), tub);
                    break;
                
                default:
                    printf("Invalid Choice\n");
                    break;

            }
        } 
        else if (pattern_type_choice == 2) {
            print_options(5, "Blinker (period 2)", "Toad (period 2)",
                             "Beacon (period 2)", "Pulsar (period 3)",
                             "Penta-decathlon(period 15)");
            getline(&input_buf, &input_size, stdin);
            pattern_choice = atoi(input_buf);
            
            switch (pattern_choice) {
                case 1:
                    put_pattern(current_gen, WID(blinker2), LEN(blinker2), blinker2);
                    break;

                case 2:
                    put_pattern(current_gen, WID(toad2), LEN(toad2), toad2);
                    break;
                    
                case 3:
                    put_pattern(current_gen, WID(beacon), LEN(beacon), beacon);
                    break;

                case 4:
                    put_pattern(current_gen, WID(pulsar3), LEN(pulsar3), pulsar3);
                    break;

                case 5:
                    put_pattern(current_gen, WID(penta15), LEN(penta15), penta15);
                    break;
                
                default:
                    printf("Invalid Choice\n");
                    break;

            }

        } 
        else if (pattern_type_choice == 3) {
            print_options(4, "Glider", "Light-weight spaceship (LWSS)",
                             "Middle-weight spaceship (MWSS)", 
                             "Heavy-weight spaceship (HWSS)");
            getline(&input_buf, &input_size, stdin);
            pattern_choice = atoi(input_buf);
            
            switch (pattern_choice) {
                case 1:
                    put_pattern(current_gen, WID(glider), LEN(glider), glider);
                    break;

                case 2:
                    put_pattern(current_gen, WID(lwss), LEN(lwss), lwss);
                    break;
                    
                case 3:
                    put_pattern(current_gen, WID(mwss), LEN(mwss), mwss);
                    break;

                case 4:
                    put_pattern(current_gen, WID(hwss), LEN(hwss), hwss);
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;

            }
        } 

        else if (pattern_type_choice == 4) {
            print_options(2, "Gosper Glider Gun", "Simkin Glider Gun");
            getline(&input_buf, &input_size, stdin);
            pattern_choice = atoi(input_buf);
            
            switch (pattern_choice) {
                case 1:
                    put_pattern(current_gen, WID(gosper_glider_gun), 
                            LEN(gosper_glider_gun), gosper_glider_gun);
                    break;

                case 2:
                    put_pattern(current_gen, WID(simkin_glider_gun), 
                            LEN(simkin_glider_gun), simkin_glider_gun);
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;
            }
        }

        else {
            printf("Invalid Choice\n");
            return 1;
        }
    }
    
    /* Build Choice */
    else if (choice == 2) {
        /* Get length and width of choice and life cells positions */ 
        printf("Enter grid length: ");
        getline(&input_buf, &input_size, stdin);
        len = atoi(input_buf);
        
        printf("Enter grid width : ");
        getline(&input_buf, &input_size, stdin);
        wid = atoi(input_buf);
        
        printf("Enter time between generations (in ms) : ");
        getline(&input_buf, &input_size, stdin);
        delta_t = atoi(input_buf);
        
        print_grid(wid, len);

        printf("Choose live cells positons: ");
        getline(&input_buf, &input_size, stdin);

        /* Get Positions from user and store it in live_cell_positions */
        live_cell_positions = malloc(strlen(input_buf) * sizeof(int));
        live_cell_numbers  = get_positions(input_buf, live_cell_positions);

        /* put positions in current_gen */
        put_positions(current_gen, live_cell_positions, live_cell_numbers, wid, len);
    }

    else {
        printf("Invalid Choice\n");
        return 1;
    }

    /* Generate and print generations */
    clear_screen();
    print_gen(current_gen, WIDTH / 6, LENGTH / 4);

    while (1) {
        usleep(delta_t * 1000);
        get_next_gen(current_gen, next_gen, WIDTH, LENGTH);
        print_gen(current_gen, WIDTH / 6, LENGTH / 4);
    }
    
    /* /1* Free generation *1/ */
    free_gen(current_gen, WIDTH);
    free_gen(next_gen, WIDTH);
    free(live_cell_positions);
    free(input_buf);

    system("reset");
    return 0;
}
