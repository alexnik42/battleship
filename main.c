#include "b_header.h"

void start_game()
{
	t_game *game;

	game = malloc(sizeof(t_game));

	game->user_map = get_user_map();
	game->user_game_map = get_user_game_map();
	game->computer_map = get_computer_map();
	game->computer_game_map = get_computer_game_map();
	simulate_game(game);
}

int main()
{
	start_game();
	return (0);
}