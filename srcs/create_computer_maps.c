#include "b_header.h"

int computer_can_place_ship(t_map *computer_map, int size, int row, int col, int direction)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (!no_ships_around(computer_map, row, col))
			return (0);
		if (direction == VERTICAL)
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
		if (direction == VERTICAL)
			row++;
		else
			col++;
		i++;
	}
}

void fill_computer_map(t_map *computer_map, t_ships *ships)
{
	int i;
	int row;
	int col;
	int direction;

	srand(time(NULL));
	i = 0;
	while (i < NUMBER_OF_SHIPS)
	{
		row = rand() % BATTLEFIELD_SIZE;
		col = rand() % BATTLEFIELD_SIZE;
		direction = rand() % 2;
		while (!computer_can_place_ship(computer_map, ships[i].size, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, ships[i].size, row, col, direction);
		i++;
	}
}

t_map *create_computer_map(t_ships *ships)
{
	t_map *computer_map;

	computer_map = malloc(sizeof(t_map));
	if (computer_map == NULL || errno)
		return (NULL);
	computer_map = create_new_map(computer_map, ships);
	fill_computer_map(computer_map, ships);
	return (computer_map);
}

t_map *create_computer_game_map(t_ships *ships)
{
	t_map *computer_user_map;

	computer_user_map = malloc(sizeof(t_map));
	if (computer_user_map == NULL || errno)
		return (NULL);
	computer_user_map = create_new_map(computer_user_map, ships);
	return (computer_user_map);
}
