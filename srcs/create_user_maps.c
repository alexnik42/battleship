#include "b_header.h"

int user_can_place_ship(int row, int col, int size, int direction, t_map *user_map)
{
	int t_row;
	int t_col;
	int t_size;
	int up;
	int down;
	int left;
	int right;

	up = down = left = right = 0;

	if (direction == NO_DIRECTION || direction == UP)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_row == BATTLEFIELD_SIZE || !no_ships_around(user_map, t_row, t_col))
			{
				up = 0;
				break;
			}
			t_row++;
			t_size--;
			up = 1;
		}
	}

	if (direction == NO_DIRECTION || direction == DOWN)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_row < 0 || !no_ships_around(user_map, t_row, t_col))
			{
				down = 0;
				break;
			}
			t_row--;
			t_size--;
			down = 1;
		}
	}

	if (direction == NO_DIRECTION || direction == RIGHT)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_col < 0 || !no_ships_around(user_map, t_row, t_col))
			{
				left = 0;
				break;
			}
			t_col--;
			t_size--;
			left = 1;
		}
	}

	if (direction == NO_DIRECTION || direction == LEFT)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_col == BATTLEFIELD_SIZE || !no_ships_around(user_map, t_row, t_col))
			{
				right = 0;
				break;
			}
			t_col++;
			t_size--;
			right = 1;
		}
	}

	return (up || down || left || right);
}

int check_position_of_first_ship(int row, int col, int size, t_map *user_map)
{
	return (no_ships_around(user_map, row, col) && user_can_place_ship(row, col, size, 0, user_map));
}

int near_latest_ship(int row, int col, int prev_row, int prev_col, int direction)
{
	if (row == prev_row + 1 && col == prev_col && (direction == UP || direction == NO_DIRECTION))
		return (1);
	if (row == prev_row - 1 && col == prev_col && (direction == DOWN || direction == NO_DIRECTION))
		return (1);
	if (row == prev_row && col == prev_col + 1 && (direction == RIGHT || direction == NO_DIRECTION))
		return (1);
	if (row == prev_row && col == prev_col - 1 && (direction == LEFT || direction == NO_DIRECTION))
		return (1);
	return (0);
}

int can_place_last_ship(int row, int col, int prev_row, int prev_col, t_map *user_map)
{
	if (row < 0 || row == BATTLEFIELD_SIZE || col < 0 || col == BATTLEFIELD_SIZE)
		return (0);

	if (user_map->battlefield[row][col] == SHIP)
		return (0);

	if (row > 0 && col > 0)
	{
		if (user_map->battlefield[row - 1][col - 1] == SHIP)
			return (0);
	}
	if (row > 0 && prev_row != row - 1)
	{
		if (user_map->battlefield[row - 1][col] == SHIP)
			return (0);
	}
	if (row > 0 && col < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row - 1][col + 1] == SHIP)
			return (0);
	}
	if (col < BATTLEFIELD_SIZE - 1 && prev_col != col + 1)
	{
		if (user_map->battlefield[row][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col < BATTLEFIELD_SIZE - 1)
	{
		if (user_map->battlefield[row + 1][col + 1] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && prev_row != row + 1)
	{
		if (user_map->battlefield[row + 1][col] == SHIP)
			return (0);
	}
	if (row < BATTLEFIELD_SIZE - 1 && col > 0)
	{
		if (user_map->battlefield[row + 1][col - 1] == SHIP)
			return (0);
	}
	if (col > 0 && prev_col != col - 1)
	{
		if (user_map->battlefield[row][col - 1] == SHIP)
			return (0);
	}
	return (1);
}

int check_position_of_other_ships(int row, int col, int prev_row, int prev_col, int size, int direction, t_map *user_map)
{
	int up;
	int down;
	int left;
	int right;
	int last_ship_placement;

	up = down = left = right = last_ship_placement = 0;
	if (size == 1)
		last_ship_placement = can_place_last_ship(row, col, prev_row, prev_col, user_map);
	else
	{
		if (row == prev_row + 1)
			up = user_can_place_ship(row + 1, col, size - 1, UP, user_map);
		else if (row == prev_row - 1)
			down = user_can_place_ship(row - 1, col, size - 1, DOWN, user_map);
		else if (col == prev_col - 1)
			left = user_can_place_ship(row, col - 1, size - 1, RIGHT, user_map);
		else if (col == prev_col + 1)
			right = user_can_place_ship(row, col + 1, size - 1, LEFT, user_map);
	}
	return (near_latest_ship(row, col, prev_row, prev_col, direction) && (up || down || left || right || last_ship_placement));
}

int get_placement_direction(int row, int col, int prev_row, int prev_col)
{
	if (row == prev_row + 1)
		return (UP);
	else if (row == prev_row - 1)
		return (DOWN);
	else if (col == prev_col + 1)
		return (RIGHT);
	else
		return (LEFT);
}

void fill_user_map(t_map *user_map, t_ships *ships)
{
	char pos[BUFF_SIZE];
	int row;
	int col;
	int prev_row;
	int prev_col;
	int direction;
	int i;
	int j;

	i = 0;
	print_user_map(user_map);
	while (i < NUMBER_OF_SHIPS)
	{
		j = 0;
		prev_row = -1;
		prev_col = -1;
		direction = NO_DIRECTION;
		while (j < ships[i].size)
		{
			printf("\nChoose #%d position for a %s [%d/%d]: ", j + 1, ships[i].name, j, ships[i].size);
			scanf("%3s", pos);
			printf("\n");
			if (!check_user_input(pos))
			{
				printf("Incorrect input. Try again\n");
				clear_stdin();
				continue;
			}
			row = pos[1] - 48;
			col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
			if (j == 0)
			{
				if (!check_position_of_first_ship(row, col, ships[i].size, user_map))
				{
					printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, j + 1, ships[i].name);
					continue;
				}
			}
			else
			{
				if (!check_position_of_other_ships(row, col, prev_row, prev_col, ships[i].size - j, direction, user_map))
				{
					printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, j + 1, ships[i].name);
					continue;
				}
				direction = direction != NO_DIRECTION ? direction : get_placement_direction(row, col, prev_row, prev_col);
			}
			user_map->battlefield[row][col] = SHIP;
			clear_screen();
			print_user_map(user_map);
			prev_row = row;
			prev_col = col;
			j++;
		}
		i++;
	}
}

t_map *create_user_map(t_ships *ships)
{
	t_map *user_map;

	user_map = malloc(sizeof(t_map));
	if (user_map == NULL || errno)
		return (NULL);
	user_map = create_new_map(user_map, ships);
	fill_user_map(user_map, ships);
	return (user_map);
}

t_map *create_user_game_map(t_ships *ships)
{
	t_map *user_game_map;

	user_game_map = malloc(sizeof(t_map));
	if (user_game_map == NULL || errno)
		return (NULL);
	user_game_map = create_new_map(user_game_map, ships);
	return (user_game_map);
}
