#include "b_header.h"

// int is_game_finished(t_map *user_map, t_map *computer_map)
// {
// 	if (user_map->ships->carrier == 1)
// 		return (-1);
// 	if (user_map->ships->battleship == 1)
// 		return (-1);
// 	if (user_map->ships->destroyer == 1)
// 		return (-1);
// 	if (user_map->ships->submarine == 1)
// 		return (-1);
// 	if (user_map->ships->patrol_boat == 1)
// 		return (-1);
// 	if (computer_map->ships->carrier == 1)
// 		return (0);
// 	if (computer_map->ships->battleship == 1)
// 		return (0);
// 	if (computer_map->ships->destroyer == 1)
// 		return (0);
// 	if (computer_map->ships->submarine == 1)
// 		return (0);
// 	if (computer_map->ships->patrol_boat == 1)
// 		return (0);
// 	return (1);
// }

int is_game_finished(t_map *user_map, t_map *computer_map)
{
	return (user_map->total_ships_size == 0 || computer_map->total_ships_size == 0);
}

void simulate_game(t_game *game)
{
	int moves;
	int row;
	int col;
	char pos[3];

	moves = 0;
	srand(time(NULL));
	while (!is_game_finished(game->user_map, game->computer_map))
	{
		printf("\e[1;1H\e[2J");
		print_game_maps(game->user_map, game->user_game_map);
		if (moves != 0)
			printf(CYN "\nLast computer turn: %c%c\n" RESET, col + 97, row + 48);
		if (moves % 2 == 0)
		{
			printf("\nChoose position to strike: ");
			scanf("%s", pos);
			printf("\n");
			row = pos[1] - 48;
			col = pos[0] - 97;
			if (game->computer_map->map[row][col] == SHIP)
			{
				game->user_game_map->map[row][col] = HIT;
				game->computer_map->total_ships_size--;
			}
			else
			{
				game->user_game_map->map[row][col] = MISS;
				moves++;
			}
		}
		else
		{
			row = rand() % MAP_SIZE;
			col = rand() % MAP_SIZE;
			while (game->computer_game_map->map[row][col] == MISS || game->computer_game_map->map[row][col] == HIT)
			{
				row = rand() % MAP_SIZE;
				col = rand() % MAP_SIZE;
			}
			if (game->user_map->map[row][col] == SHIP)
			{
				game->user_map->map[row][col] = HIT;
				game->computer_game_map->map[row][col] = HIT;
				game->user_map->total_ships_size--;
			}
			else
			{
				game->computer_game_map->map[row][col] = MISS;
				game->user_map->map[row][col] = MISS;
				moves++;
			}
		}
	}
	printf("\e[1;1H\e[2J");
	print_game_maps(game->user_map, game->user_game_map);
	printf("\n");
	print_computer_map(game->computer_map);
	game->user_map->total_ships_size == 0 ? printf("\nCOMPUTER HAS WON! \n") : printf("\nUSER HAS WON! \n");
}