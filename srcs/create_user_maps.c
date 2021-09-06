#include "b_header.h"

int is_enough_space_for_a_ship(int row, int col, int size, int direction, t_map *user_map)
{
	int t_row;
	int t_col;
	int t_size;
	int up;
	int down;
	int left;
	int right;

	up = down = left = right = 0;

	if (direction == 0 || direction == 1)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_row == BATTLEFIELD_SIZE || check_surrounding(user_map, t_row, t_col) == 0)
			{
				up = 0;
				break;
			}
			t_row++;
			t_size--;
			up = 1;
		}
	}

	if (direction == 0 || direction == -1)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_row < 0 || check_surrounding(user_map, t_row, t_col) == 0)
			{
				down = 0;
				break;
			}
			t_row--;
			t_size--;
			down = 1;
		}
	}

	if (direction == 0 || direction == 2)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_col < 0 || check_surrounding(user_map, t_row, t_col) == 0)
			{
				left = 0;
				break;
			}
			t_col--;
			t_size--;
			left = 1;
		}
	}

	if (direction == 0 || direction == -2)
	{
		t_row = row;
		t_col = col;
		t_size = size;
		while (t_size > 0)
		{
			if (t_col == BATTLEFIELD_SIZE || check_surrounding(user_map, t_row, t_col) == 0)
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
	return (check_surrounding(user_map, row, col) && is_enough_space_for_a_ship(row, col, size, 0, user_map));
}

int is_prev_ship_nearby(int row, int col, int prev_row, int prev_col, int direction)
{
	if (row == prev_row + 1 && col == prev_col && (direction == 1 || direction == 0))
		return (1);
	if (row == prev_row - 1 && col == prev_col && (direction == -1 || direction == 0))
		return (1);
	if (row == prev_row && col == prev_col + 1 && (direction == 2 || direction == 0))
		return (1);
	if (row == prev_row && col == prev_col - 1 && (direction == -2 || direction == 0))
		return (1);
	return (0);
}

int last_ship(int row, int col, int prev_row, int prev_col, t_map *user_map)
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
	int single_placement;

	up = down = left = right = single_placement = 0;
	if (size == 1)
	{
		single_placement = last_ship(row, col, prev_row, prev_col, user_map);
	}
	else
	{
		if (row == prev_row + 1)
			up = is_enough_space_for_a_ship(row + 1, col, size - 1, 1, user_map);
		else if (row == prev_row - 1)
			down = is_enough_space_for_a_ship(row - 1, col, size - 1, -1, user_map);
		else if (col == prev_col - 1)
			left = is_enough_space_for_a_ship(row, col - 1, size - 1, 2, user_map);
		else if (col == prev_col + 1)
			right = is_enough_space_for_a_ship(row, col + 1, size - 1, -2, user_map);
	}

	return (is_prev_ship_nearby(row, col, prev_row, prev_col, direction) && (up || down || left || right || single_placement));
}

int get_placement_direction(int row, int col, int prev_row, int prev_col)
{
	if (row == prev_row + 1)
		return (1);
	else if (row == prev_row - 1)
		return (-1);
	else if (col == prev_col + 1)
		return (2);
	else
		return (-2);
}

void fill_user_map(t_map *user_map)
{
	char pos[3];
	int row;
	int col;
	int prev_row;
	int prev_col;
	int direction;
	int i;

	prev_row = 0;
	prev_col = 0;
	i = 0;
	direction = 0;
	print_single_map(user_map);
	while (i < CARRIER_SIZE)
	{
		printf("\nChoose #%d position for a %s [%d/%d]: ", i + 1, CARRIER_NAME, i, CARRIER_SIZE);
		scanf("%2s", pos);
		printf("\n");
		if (check_user_input(pos) == 0)
		{
			printf("Incorrect input. Try again\n");
			clear_stdin();
			continue;
		}
		row = pos[1] - 48;
		col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
		if (i == 0)
		{
			if (check_position_of_first_ship(row, col, CARRIER_SIZE, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, CARRIER_NAME);
				continue;
			}
		}
		else
		{
			if (check_position_of_other_ships(row, col, prev_row, prev_col, CARRIER_SIZE - i, direction, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, CARRIER_NAME);
				continue;
			}
			direction = direction != 0 ? direction : get_placement_direction(row, col, prev_row, prev_col);
		}
		user_map->battlefield[row][col] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		prev_row = row;
		prev_col = col;
		i++;
	}

	i = 0;
	direction = 0;
	while (i < BATTLESHIP_SIZE)
	{
		printf("\nChoose #%d position for a %s [%d/%d]: ", i + 1, BATTLESHIP_NAME, i, BATTLESHIP_SIZE);
		scanf("%2s", pos);
		printf("\n");
		if (check_user_input(pos) == 0)
		{
			printf("Incorrect input. Try again\n");
			clear_stdin();
			continue;
		}
		row = pos[1] - 48;
		col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
		if (i == 0)
		{
			if (check_position_of_first_ship(row, col, BATTLESHIP_SIZE, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, BATTLESHIP_NAME);
				continue;
			}
		}
		else
		{
			if (check_position_of_other_ships(row, col, prev_row, prev_col, BATTLESHIP_SIZE - i, direction, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, BATTLESHIP_NAME);
				continue;
			}
			direction = direction != 0 ? direction : get_placement_direction(row, col, prev_row, prev_col);
		}
		user_map->battlefield[row][col] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		prev_row = row;
		prev_col = col;
		i++;
	}

	i = 0;
	direction = 0;
	while (i < DESTROYER_SIZE)
	{
		printf("\nChoose #%d position for a %s [%d/%d]: ", i + 1, DESTROYER_NAME, i, DESTROYER_SIZE);
		scanf("%2s", pos);
		printf("\n");
		if (check_user_input(pos) == 0)
		{
			printf("Incorrect input. Try again\n");
			clear_stdin();
			continue;
		}
		row = pos[1] - 48;
		col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
		if (i == 0)
		{
			if (check_position_of_first_ship(row, col, DESTROYER_SIZE, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, DESTROYER_NAME);
				continue;
			}
		}
		else
		{
			if (check_position_of_other_ships(row, col, prev_row, prev_col, DESTROYER_SIZE - i, direction, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, DESTROYER_NAME);
				continue;
			}
			direction = direction != 0 ? direction : get_placement_direction(row, col, prev_row, prev_col);
		}
		user_map->battlefield[row][col] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		prev_row = row;
		prev_col = col;
		i++;
	}

	i = 0;
	direction = 0;
	while (i < SUBMARINE_SIZE)
	{
		printf("\nChoose #%d position for a %s [%d/%d]: ", i + 1, SUBMARINE_NAME, i, SUBMARINE_SIZE);
		scanf("%2s", pos);
		printf("\n");
		if (check_user_input(pos) == 0)
		{
			printf("Incorrect input. Try again\n");
			clear_stdin();
			continue;
		}
		row = pos[1] - 48;
		col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
		if (i == 0)
		{
			if (check_position_of_first_ship(row, col, SUBMARINE_SIZE, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, SUBMARINE_NAME);
				continue;
			}
		}
		else
		{
			if (check_position_of_other_ships(row, col, prev_row, prev_col, SUBMARINE_SIZE - i, direction, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, SUBMARINE_NAME);
				continue;
			}
			direction = direction != 0 ? direction : get_placement_direction(row, col, prev_row, prev_col);
		}
		user_map->battlefield[row][col] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		prev_row = row;
		prev_col = col;
		i++;
	}

	i = 0;
	direction = 0;
	while (i < PATROL_BOAT_SIZE)
	{
		printf("\nChoose #%d position for a %s [%d/%d]: ", i + 1, PATROL_BOAT_NAME, i, PATROL_BOAT_SIZE);
		scanf("%2s", pos);
		printf("\n");
		if (check_user_input(pos) == 0)
		{
			printf("Incorrect input. Try again\n");
			clear_stdin();
			continue;
		}
		row = pos[1] - 48;
		col = pos[0] - (pos[0] >= 97 && pos[0] <= 122 ? 97 : 65);
		if (i == 0)
		{
			if (check_position_of_first_ship(row, col, PATROL_BOAT_SIZE, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, PATROL_BOAT_NAME);
				continue;
			}
		}
		else
		{
			if (check_position_of_other_ships(row, col, prev_row, prev_col, PATROL_BOAT_SIZE - i, direction, user_map) == 0)
			{
				printf("%c%c is an invalid #%d position for a %s\n", col + 97, row + 48, i + 1, PATROL_BOAT_NAME);
				continue;
			}
			direction = direction != 0 ? direction : get_placement_direction(row, col, prev_row, prev_col);
		}
		user_map->battlefield[row][col] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		prev_row = row;
		prev_col = col;
		i++;
	}
}

t_map *create_user_map(void)
{
	t_map *user_map;

	user_map = malloc(sizeof(t_map));
	if (user_map == NULL || errno)
		return (NULL);
	user_map = create_new_map(user_map);
	fill_user_map(user_map);
	return (user_map);
}

t_map *create_user_game_map(void)
{
	t_map *user_game_map;

	user_game_map = malloc(sizeof(t_map));
	if (user_game_map == NULL || errno)
		return (NULL);
	user_game_map = create_new_map(user_game_map);
	return (user_game_map);
}
