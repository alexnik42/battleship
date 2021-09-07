#ifndef B_HEADER_H
#define B_HEADER_H

#define BATTLEFIELD_SIZE 10
#define NUMBER_OF_SHIPS 5

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

#define BUFF_SIZE 4

#define EMPTY '.'
#define SHIP 'S'
#define HIT 'X'
#define MISS 'M'

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2
#define VERTICAL 1
#define HORIZONTAL -1
#define NO_DIRECTION 0

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

typedef struct s_ships
{
	char *name;
	int size;
} t_ships;

// start_new_game.c
void start_new_game(void);

// print_error.c
void print_error(void);

// clear_io.c
void clear_stdin(void);
void clear_screen(void);

// free_memory.c
void free_battlefield(char **battlefield, int size);
void free_map(t_map *map);
void free_ships(t_ships *ships);
void free_game_map(t_map *map);
void free_game(t_game *game);
void free_all_memory(t_game *game, t_ships *ships);

// create_ships.c
t_ships *create_ships();

// create_new_map.c
t_map *create_new_map(t_map *map, t_ships *ships);

// create_user_maps.c
t_map *create_user_map(t_ships *ships);
t_map *create_user_game_map(t_ships *ships);

// create_computer_maps.c
t_map *create_computer_map(t_ships *ships);
t_map *create_computer_game_map(t_ships *ships);

// print_maps.c
void print_user_map(t_map *user_map);
void print_computer_map(t_map *computer_map);
void print_game_maps(t_map *user_map, t_map *game_map);

// check_validity.c
int no_ships_around(t_map *map, int row, int col);
int check_user_input(char *pos);

// simulate_game.c
void simulate_game(t_game *game);

// next_computer_move.c
void next_computer_move(int *row, int *col, int last_hit_row, int last_hit_col, t_game *game);

#endif
