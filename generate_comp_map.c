#include "b_header.h"

int check_surrounding(t_map *computer_map, int row, int col)
{
	if (row < 0 || row == BATTLEFIELD_SIZE || col < 0 || col == BATTLEFIELD_SIZE)
		return (0);

	if (computer_map->battlefield[row][col] == SHIP)
		return (0);

	if (row > 0 && col > 0)
	{
		if (computer_map->battlefield[row - 1][col - 1] == SHIP)
			return (0);
	}
	if (row > 0)
	{
		if (computer_map->battlefield[row - 1][col] == SHIP)
			return (0);
	}
	if (row > 0 && col < BATTLEFIELD_SIZE - 1)
	{
		if (computer_map->battlefield[row - 1][col + 1] == SHIP)
			return (0);
	}
	if (col < BATTLEFIELD_SIZE - 1)
	{
		if (computer_map->battlefield[row][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col < BATTLEFIELD_SIZE - 1)
	{
		if (computer_map->battlefield[row + 1][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1)
	{
		if (computer_map->battlefield[row + 1][col] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col > 0)
	{
		if (computer_map->battlefield[row + 1][col - 1] == SHIP)
			return (0);
	}
	if (col > 0)
	{
		if (computer_map->battlefield[row][col - 1] == SHIP)
			return (0);
	}
	return (1);
}

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
	int q;

	srand(time(NULL));
	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	q = 0;
	while (q < CARRIER_Q)
	{
		while (!can_place_ship(computer_map, CARRIER_S, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, CARRIER_S, row, col, direction);
		q++;
	}

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	q = 0;
	while (q < BATTLESHIP_Q)
	{
		while (!can_place_ship(computer_map, BATTLESHIP_S, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, BATTLESHIP_S, row, col, direction);
		q++;
	}

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	q = 0;
	while (q < DESTROYER_Q)
	{
		while (!can_place_ship(computer_map, DESTROYER_S, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, DESTROYER_S, row, col, direction);
		q++;
	}

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	q = 0;
	while (q < SUBMARINE_Q)
	{
		while (!can_place_ship(computer_map, SUBMARINE_S, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, SUBMARINE_S, row, col, direction);
		q++;
	}

	row = rand() % BATTLEFIELD_SIZE;
	col = rand() % BATTLEFIELD_SIZE;
	direction = rand() % 2;
	q = 0;
	while (q < PATROL_BOAT_Q)
	{
		while (!can_place_ship(computer_map, PATROL_BOAT_S, row, col, direction))
		{
			row = rand() % BATTLEFIELD_SIZE;
			col = rand() % BATTLEFIELD_SIZE;
			direction = rand() % 2;
		}
		place_ship(computer_map, PATROL_BOAT_S, row, col, direction);
		q++;
	}
}

t_map *get_computer_map()
{
	t_map *computer_map;

	computer_map = malloc(sizeof(t_map));
	if (computer_map == NULL || errno)
		return (NULL);
	computer_map = allocate_memory(computer_map);
	if (computer_map == NULL)
		return (NULL);
	computer_map = initialize_empty_map(computer_map);
	fill_comp_map(computer_map);
	return (computer_map);
}

t_map *get_computer_game_map()
{
	t_map *computer_user_map;

	computer_user_map = malloc(sizeof(t_map));
	if (computer_user_map == NULL || errno)
		return (NULL);
	computer_user_map = allocate_memory(computer_user_map);
	if (computer_user_map == NULL)
		return (NULL);
	computer_user_map = initialize_empty_map(computer_user_map);
	return (computer_user_map);
}
