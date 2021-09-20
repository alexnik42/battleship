#include "b_header.h"

int get_shooting_direction(int row, int col, t_map *computer_game_map)
{
	while (row > 0 && computer_game_map->battlefield[row - 1][col] == HIT)
		row--;
	while (col > 0 && computer_game_map->battlefield[row][col - 1] == HIT)
		col--;

	if (row + 1 < BATTLEFIELD_SIZE && computer_game_map->battlefield[row + 1][col] == HIT)
		return (VERTICAL);
	else if (col + 1 < BATTLEFIELD_SIZE && computer_game_map->battlefield[row][col + 1] == HIT)
		return (HORIZONTAL);
	else
		return (NO_DIRECTION);
}

void next_computer_move(int *row, int *col, int last_hit_row, int last_hit_col, t_game *game)
{
	int direction;

	direction = get_shooting_direction(last_hit_row, last_hit_col, game->computer_game_map);
	if (direction == NO_DIRECTION)
	{
		if (last_hit_row > 0 && game->computer_game_map->battlefield[last_hit_row - 1][last_hit_col] == EMPTY)
		{
			*row = last_hit_row - 1;
			*col = last_hit_col;
		}
		else if (last_hit_col > 0 && game->computer_game_map->battlefield[last_hit_row][last_hit_col - 1] == EMPTY)
		{
			*row = last_hit_row;
			*col = last_hit_col - 1;
		}
		else if (last_hit_row < BATTLEFIELD_SIZE - 1 && game->computer_game_map->battlefield[last_hit_row + 1][last_hit_col] == EMPTY)
		{
			*row = last_hit_row + 1;
			*col = last_hit_col;
		}
		else
		{
			*row = last_hit_row;
			*col = last_hit_col + 1;
		}
	}
	else if (direction == VERTICAL)
	{
		while (last_hit_row < BATTLEFIELD_SIZE && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == HIT)
			last_hit_row++;
		if (last_hit_row != BATTLEFIELD_SIZE && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == EMPTY)
		{
			*row = last_hit_row;
			*col = last_hit_col;
		}
		else
		{
			last_hit_row--;
			while (last_hit_row > 0 && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == HIT)
				last_hit_row--;
			*row = last_hit_row;
			*col = last_hit_col;
		}
	}
	else
	{
		while (last_hit_col < BATTLEFIELD_SIZE && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == HIT)
			last_hit_col++;
		if (last_hit_col != BATTLEFIELD_SIZE && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == EMPTY)
		{
			*row = last_hit_row;
			*col = last_hit_col;
		}
		else
		{
			last_hit_col--;
			while (last_hit_col > 0 && game->computer_game_map->battlefield[last_hit_row][last_hit_col] == HIT)
				last_hit_col--;
			*row = last_hit_row;
			*col = last_hit_col;
		}
	}
}
