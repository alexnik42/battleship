#ifndef B_HEADER_HEAD
#define B_HEADER_HEAD

#define BATTLEFIELD_SIZE 10

#define CARRIER_S 5
#define BATTLESHIP_S 4
#define DESTROYER_S 3
#define SUBMARINE_S 3
#define PATROL_BOAT_S 2

#define CARRIER_Q 1
#define BATTLESHIP_Q 1
#define DESTROYER_Q 1
#define SUBMARINE_Q 1
#define PATROL_BOAT_Q 1

#define EMPTY '.'
#define SHIP 'S'
#define HIT 'X'
#define MISS 'M'

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef struct s_ships
{
	int carrier;
	int battleship;
	int destroyer;
	int submarine;
	int patrol_boat;
} t_ships;

typedef struct s_map
{
	char **battlefield;
	int height;
	int width;
	t_ships *ships;
	int total_ships_size;
} t_map;

typedef struct s_game
{
	t_map *user_map;
	t_map *user_game_map;
	t_map *computer_map;
	t_map *computer_game_map;
} t_game;

// get_user_map.c
t_map *get_user_map();
t_map *get_user_game_map();

// get_comp_map.c
t_map *get_computer_map();
t_map *get_computer_game_map();

// print_map.c
void print_single_map(t_map *user_map);
void print_computer_map(t_map *computer_map);
void print_game_maps(t_map *user_map, t_map *game_map);

// create_map.c
t_map *allocate_memory(t_map *map);
t_map *initialize_empty_map(t_map *map);

// start_game.c
void new_game();

// simulate_game.c
void simulate_game(t_game *game);

// computer_moves.c
void next_computer_move(int *row, int *col, int last_hit_row, int last_hit_col, t_game *game);

// free_memory.c
void free_battlefield(char **battlefield, int size);
void free_ships(t_ships *ships);
void free_map(t_map *map);
void free_game_map(t_map *map);
void free_game(t_game *game);
void free_all_memory(t_game *game);

// handle_errors.c
void handle_errors(void);

#endif
