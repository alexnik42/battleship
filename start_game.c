#include "b_header.h"

void new_game()
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (game == NULL || errno)
	{
		handle_errors();
		return;
	}

	game->user_map = get_user_map();
	if (game->user_map == NULL || errno)
	{
		handle_errors();
		free_game(game);
		return;
	}

	game->user_game_map = get_user_game_map();
	if (game->user_game_map == NULL || errno)
	{
		handle_errors();
		free_game_map(game->user_map);
		free_game(game);
		return;
	}

	game->computer_map = get_computer_map();
	if (game->computer_map == NULL || errno)
	{
		handle_errors();
		free_game_map(game->user_map);
		free_game_map(game->user_game_map);
		free_game(game);
		return;
	}

	game->computer_game_map = get_computer_game_map();
	if (game->computer_game_map == NULL || errno)
	{
		handle_errors();
		free_game_map(game->user_map);
		free_game_map(game->user_game_map);
		free_game_map(game->computer_map);
		free_game(game);
		return;
	}

	simulate_game(game);
	free_all_memory(game);
}
