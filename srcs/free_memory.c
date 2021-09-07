#include "b_header.h"

void free_battlefield(char **battlefield, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(battlefield[i]);
		i++;
	}
	free(battlefield);
}

void free_map(t_map *map)
{
	free(map);
}

void free_ships(t_ships *ships)
{
	free(ships);
}

void free_game_map(t_map *map)
{
	free_battlefield(map->battlefield, BATTLEFIELD_SIZE);
	free_map(map);
}

void free_game(t_game *game)
{
	free(game);
}

void free_all_memory(t_game *game, t_ships *ships)
{
	free(ships);
	free_game_map(game->user_map);
	free_game_map(game->user_game_map);
	free_game_map(game->computer_map);
	free_game_map(game->computer_game_map);

	free_game(game);
}
