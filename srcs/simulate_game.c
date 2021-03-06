#include "b_header.h"

int game_finished(t_map *user_map, t_map *computer_map)
{
	return (user_map->ships_units_left == 0 || computer_map->ships_units_left == 0);
}

int killed_ship(int row, int col, t_map *map)
{
	int t_row;
	int t_col;

	t_row = row;
	t_col = col;
	while (t_row > 0 && map->battlefield[t_row][t_col] == HIT)
		t_row--;
	if (map->battlefield[t_row][t_col] == SHIP)
		return (0);

	t_row = row;
	t_col = col;
	while (t_col > 0 && map->battlefield[t_row][t_col] == HIT)
		t_col--;
	if (map->battlefield[t_row][t_col] == SHIP)
		return (0);

	t_row = row;
	t_col = col;
	while (t_row < BATTLEFIELD_SIZE - 1 && map->battlefield[t_row][t_col] == HIT)
		t_row++;
	if (map->battlefield[t_row][t_col] == SHIP)
		return (0);

	t_row = row;
	t_col = col;
	while (t_col < BATTLEFIELD_SIZE - 1 && map->battlefield[t_row][t_col] == HIT)
		t_col++;
	if (map->battlefield[t_row][t_col] == SHIP)
		return (0);
	return (1);
}

void mark_space(int row, int col, t_map *user_map, t_map *computer_map)
{
	if (row > 0 && col > 0)
	{
		if (user_map->battlefield[row - 1][col - 1] != HIT)
		{
			user_map->battlefield[row - 1][col - 1] = MISS;
			computer_map->battlefield[row - 1][col - 1] = MISS;
		}
	}
	if (row > 0)
	{
		if (user_map->battlefield[row - 1][col] != HIT)
		{
			user_map->battlefield[row - 1][col] = MISS;
			computer_map->battlefield[row - 1][col] = MISS;
		}
	}
	if (row > 0 && col < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row - 1][col + 1] != HIT)
		{
			user_map->battlefield[row - 1][col + 1] = MISS;
			computer_map->battlefield[row - 1][col + 1] = MISS;
		}
	}
	if (col < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row][col + 1] != HIT)
		{
			user_map->battlefield[row][col + 1] = MISS;
			computer_map->battlefield[row][col + 1] = MISS;
		}
	}
	if (row < BATTLEFIELD_SIZE - 1 && col < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row + 1][col + 1] != HIT)
		{
			user_map->battlefield[row + 1][col + 1] = MISS;
			computer_map->battlefield[row + 1][col + 1] = MISS;
		}
	}
	if (row < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row + 1][col] != HIT)
		{
			user_map->battlefield[row + 1][col] = MISS;
			computer_map->battlefield[row + 1][col] = MISS;
		}
	}
	if (row < BATTLEFIELD_SIZE - 1 && col > 0)
	{
		if (user_map->battlefield[row + 1][col - 1] != HIT)
		{
			user_map->battlefield[row + 1][col - 1] = MISS;
			computer_map->battlefield[row + 1][col - 1] = MISS;
		}
	}
	if (col > 0)
	{
		if (user_map->battlefield[row][col - 1] != HIT)
		{
			user_map->battlefield[row][col - 1] = MISS;
			computer_map->battlefield[row][col - 1] = MISS;
		}
	}
}

void mark_space_around_ships(int row, int col, t_map *user_map, t_map *computer_map)
{
	mark_space(row, col, user_map, computer_map);
	while (row > 0 && user_map->battlefield[row - 1][col] == HIT)
		mark_space((row-- - 1), col, user_map, computer_map);
	while (row < BATTLEFIELD_SIZE - 1 && user_map->battlefield[row + 1][col] == HIT)
		mark_space((row++ + 1), col, user_map, computer_map);
	while (col > 0 && user_map->battlefield[row][col - 1] == HIT)
		mark_space(row, (col-- - 1), user_map, computer_map);
	while (col < BATTLEFIELD_SIZE - 1 && user_map->battlefield[row][col + 1] == HIT)
		mark_space(row, (col++ + 1), user_map, computer_map);
}

void simulate_game(t_game *game)
{
	int moves;
	int row;
	int col;
	char pos[BUFF_SIZE];
	int is_computer_move;
	int last_hit;
	int last_hit_row;
	int last_hit_col;

	moves = 0;
	last_hit = 0;
	is_computer_move = 0;
	srand(time(NULL));
	clear_screen();
	print_game_maps(game->user_map, game->user_game_map);
	while (!game_finished(game->user_map, game->computer_map))
	{
		if (moves % 2 == 0)
		{
			printf("\nChoose position to strike: ");
			scanf("%s", pos);
			printf("\n");
			if (!check_user_input(pos))
			{
				printf("Incorrect input. Try again\n");
				clear_stdin();
				continue;
			}
			row = pos[1] - 48;
			col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
			if (game->user_game_map->battlefield[row][col] != EMPTY)
			{
				printf("%c%c is an invalid position for a strike\n", col + 97, row + 48);
				continue;
			}
			if (game->computer_map->battlefield[row][col] == SHIP)
			{
				game->user_game_map->battlefield[row][col] = HIT;
				game->computer_map->battlefield[row][col] = HIT;
				game->computer_map->ships_units_left--;
				if (killed_ship(row, col, game->computer_map))
					mark_space_around_ships(row, col, game->user_game_map, game->computer_map);
			}
			else
			{
				game->user_game_map->battlefield[row][col] = MISS;
				game->computer_map->battlefield[row][col] = MISS;
				moves++;
			}
			is_computer_move = 0;
		}
		else
		{
			printf("\nComputer is thinking...\n");
			sleep(1);
			if (!last_hit)
			{
				row = rand() % BATTLEFIELD_SIZE;
				col = rand() % BATTLEFIELD_SIZE;
				while (game->computer_game_map->battlefield[row][col] == MISS || game->computer_game_map->battlefield[row][col] == HIT)
				{
					row = rand() % BATTLEFIELD_SIZE;
					col = rand() % BATTLEFIELD_SIZE;
				}
			}
			else
			{
				next_computer_move(&row, &col, last_hit_row, last_hit_col, game);
			}
			if (game->user_map->battlefield[row][col] == SHIP)
			{
				game->user_map->battlefield[row][col] = HIT;
				game->computer_game_map->battlefield[row][col] = HIT;
				game->user_map->ships_units_left--;
				last_hit = 1;
				last_hit_row = row;
				last_hit_col = col;
				if (killed_ship(row, col, game->user_map))
				{
					mark_space_around_ships(row, col, game->user_map, game->computer_game_map);
					last_hit = 0;
				}
			}
			else
			{
				game->computer_game_map->battlefield[row][col] = MISS;
				game->user_map->battlefield[row][col] = MISS;
				moves++;
			}
			is_computer_move = 1;
		}
		clear_screen();
		print_game_maps(game->user_map, game->user_game_map);
		if (is_computer_move)
			printf(CYN "\nLast computer turn: %c%c\n" RESET, col + 97, row + 48);
	}
	clear_screen();
	print_game_maps(game->user_map, game->user_game_map);
	printf("\n");
	print_computer_map(game->computer_map);
	game->user_map->ships_units_left == 0 ? printf("\nCOMPUTER HAS WON! \n\n") : printf("\nUSER HAS WON! \n\n");
}
