#include "b_header.h"

int no_ships_around(t_map *map, int row, int col)
{
	if (row < 0 || row == BATTLEFIELD_SIZE || col < 0 || col == BATTLEFIELD_SIZE)
		return (0);

	if (map->battlefield[row][col] == SHIP)
		return (0);

	if (row > 0 && col > 0)
	{
		if (map->battlefield[row - 1][col - 1] == SHIP)
			return (0);
	}
	if (row > 0)
	{
		if (map->battlefield[row - 1][col] == SHIP)
			return (0);
	}
	if (row > 0 && col < BATTLEFIELD_SIZE - 1)
	{
		if (map->battlefield[row - 1][col + 1] == SHIP)
			return (0);
	}
	if (col < BATTLEFIELD_SIZE - 1)
	{
		if (map->battlefield[row][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col < BATTLEFIELD_SIZE - 1)
	{
		if (map->battlefield[row + 1][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1)
	{
		if (map->battlefield[row + 1][col] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col > 0)
	{
		if (map->battlefield[row + 1][col - 1] == SHIP)
			return (0);
	}
	if (col > 0)
	{
		if (map->battlefield[row][col - 1] == SHIP)
			return (0);
	}
	return (1);
}

int check_user_input(char *pos)
{
	int len;

	len = strlen(pos);
	if (len != 2)
		return 0;
	if (!((pos[0] >= 97 && pos[0] <= 122) || (pos[0] >= 65 && pos[0] <= 90)))
		return (0);
	if (!(pos[1] >= 48 && pos[1] <= 57))
		return (0);
	return (1);
}
