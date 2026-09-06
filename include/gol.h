extern int wid;
extern int len;

#define IN  1
#define OUT 0

#define LENGTH 200
#define WIDTH  150

#define MAX_WORD_LEM 256

/* Functions in gol.c */
void start_game(int** current_gen, int num, int wid, int len);
void get_next_gen(int** current_gen,  int **next_gen, int wid, int len);
int  next_state(int x, int y, int** world, int wid, int len);
void print_gen(int** gen, int wid, int len);
int  equal(int** gen1,int** gen2,int wid,int len);
void free_gen(int** gen, int wid);

/* Funcitons in utils.c */
void print_options(int count, ...);
void print_grid(int wid, int len);
int  get_positions(char* str, int* positions);
void put_positions(int** gen, int* pos, int pos_num, int wid, int len);
void put_pattern(int** gen, int wid, int len, int pattern[wid][len]);
void clear_screen();
