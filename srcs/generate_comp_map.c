#include "b_header.h"

int can_place_ship(t_map *computer_map, int size, int row, int col, int direction)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (!check_surrounding(computer_map, row, col))
			return (0);
		if (direction == 1)
			row++;
		else
			col++;
		i++;
	}
	return (1);
}

void place_ship(t_map *computer_map, int size, int row, int col, int direction)
{
	int i;

	i = 0;
	while (i < size)
	{
		computer_map->battlefield[row][col] = SHIP;
		if (direction == 1)
			row++;
		else
			col++;
		i++;
	}
}

void fill_comp_map(t_map *computer_map)
{
	int row;
	int col;
	int direction;

	srand(time(NULL));
	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	while (!can_place_ship(computer_map, CARRIER_SIZE, row, col, direction))
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
	}
	place_ship(computer_map, CARRIER_SIZE, row, col, direction);

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	while (!can_place_ship(computer_map, BATTLESHIP_SIZE, row, col, direction))
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
	}
	place_ship(computer_map, BATTLESHIP_SIZE, row, col, direction);

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	while (!can_place_ship(computer_map, DESTROYER_SIZE, row, col, direction))
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
	}
	place_ship(computer_map, DESTROYER_SIZE, row, col, direction);

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	while (!can_place_ship(computer_map, SUBMARINE_SIZE, row, col, direction))
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
	}
	place_ship(computer_map, SUBMARINE_SIZE, row, col, direction);

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	while (!can_place_ship(computer_map, PATROL_BOAT_SIZE, row, col, direction))
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
	}
	place_ship(computer_map, PATROL_BOAT_SIZE, row, col, direction);
}

t_map *get_computer_map()
{
	t_map *computer_map;

	computer_map = malloc(sizeof(t_map));
	if (computer_map == NULL || errno)
		return (NULL);
	computer_map = create_new_map(computer_map);
	fill_comp_map(computer_map);
	return (computer_map);
}

t_map *get_computer_game_map()
{
	t_map *computer_user_map;

	computer_user_map = malloc(sizeof(t_map));
	if (computer_user_map == NULL || errno)
		return (NULL);
	computer_user_map = create_new_map(computer_user_map);
	return (computer_user_map);
}
