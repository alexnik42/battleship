#ifndef B_HEADER_H
#define B_HEADER_H

#define BATTLEFIELD_SIZE 10

#define CARRIER_NAME "CARRIER"
#define BATTLESHIP_NAME "BATTLESHIP"
#define DESTROYER_NAME "DESTROYER"
#define SUBMARINE_NAME "SUBMARINE"
#define PATROL_BOAT_NAME "PATROL BOAT"

#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define DESTROYER_SIZE 3
#define SUBMARINE_SIZE 3
#define PATROL_BOAT_SIZE 2

#define EMPTY '.'
#define SHIP 'S'
#define HIT 'X'
#define MISS 'M'

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef struct s_map
{
	char **battlefield;
	int height;
	int width;
	int ships_units_left;
} t_map;

typedef struct s_game
{
	t_map *user_map;
	t_map *user_game_map;
	t_map *computer_map;
	t_map *computer_game_map;
} t_game;

// start_new_game.c
void start_new_game(void);

// print_error.c
void print_error(void);

// create_new_map.c
t_map *create_new_map(t_map *map);

// create_user_maps.c
t_map *create_user_map(void);
t_map *create_user_game_map(void);

// get_comp_map.c
t_map *get_computer_map();
t_map *get_computer_game_map();

// print_map.c
void print_single_map(t_map *user_map);
void print_computer_map(t_map *computer_map);
void print_game_maps(t_map *user_map, t_map *game_map);

// check_validity.c
int check_surrounding(t_map *map, int row, int col);
int check_user_input(char *pos);
void clear_stdin();

// simulate_game.c
void simulate_game(t_game *game);

// computer_moves.c
void next_computer_move(int *row, int *col, int last_hit_row, int last_hit_col, t_game *game);

// free_memory.c
void free_battlefield(char **battlefield, int size);
void free_map(t_map *map);
void free_game_map(t_map *map);
void free_game(t_game *game);
void free_all_memory(t_game *game);

#endif
