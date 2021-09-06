#include "b_header.h"

int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

int get_direction(int row, int col, t_map *computer_game_map)
{
	while (row > 0 && computer_game_map->battlefield[row - 1][col] == HIT)
		row--;
	while (col > 0 && computer_game_map->battlefield[row][col - 1] == HIT)
		col--;

	if (computer_game_map->battlefield[row + 1][col] == HIT)
		return (1);
	else if (computer_game_map->battlefield[row][col + 1] == HIT)
		return (0);
	else
		return (-1);
}

int get_longest_streak(int row, int col, t_map *computer_game_map)
{
	int curr_streak;
	int direction;

	curr_streak = 0;
	direction = get_direction(row, col, computer_game_map);
	while (row > 0 && computer_game_map->battlefield[row - 1][col] == HIT)
		row--;
	while (col > 0 && computer_game_map->battlefield[row][col - 1] == HIT)
		col--;

	if (direction == -1)
		curr_streak = 1;
	else if (direction == 0)
	{
		while (col < BATTLEFIELD_SIZE && computer_game_map->battlefield[row][col] == HIT)
		{
			col++;
			curr_streak++;
		}
	}
	else
	{
		while (row < BATTLEFIELD_SIZE && computer_game_map->battlefield[row][col] == HIT)
		{
			row++;
			curr_streak++;
		}
	}
	return (curr_streak);
}

void next_computer_move(int *row, int *col, int last_hit_row, int last_hit_col, t_game *game)
{
	int longest_streak;
	int direction;

	longest_streak = get_longest_streak(last_hit_row, last_hit_col, game->computer_game_map);
	direction = get_direction(last_hit_row, last_hit_col, game->computer_game_map);
	if (longest_streak == 1)
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
	else
	{
		if (direction == 1)
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
}