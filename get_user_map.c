#include "b_header.h"

void fill_user_map(t_map *user_map)
{
	char pos[3];
	int i;

	i = 0;
	print_single_map(user_map);
	while (i < CARRIER_S * CARRIER_Q)
	{
		printf("\nChoose position for CARRIER: ");
		scanf("%s", pos);
		printf("\n");
		user_map->map[pos[1] - 48][pos[0] - 97] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		i++;
	}

	i = 0;
	while (i < BATTLESHIP_S * BATTLESHIP_Q)
	{
		printf("\nChoose position for BATTLESHIP: ");
		scanf("%s", pos);
		printf("\n");
		user_map->map[pos[1] - 48][pos[0] - 97] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		i++;
	}

	i = 0;
	while (i < DESTROYER_S * DESTROYER_Q)
	{
		printf("\nChoose position for DESTROYER: ");
		scanf("%s", pos);
		printf("\n");
		user_map->map[pos[1] - 48][pos[0] - 97] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		i++;
	}

	i = 0;
	while (i < SUBMARINE_S * SUBMARINE_Q)
	{
		printf("\nChoose position for SUBMARINE: ");
		scanf("%s", pos);
		printf("\n");
		user_map->map[pos[1] - 48][pos[0] - 97] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		i++;
	}

	i = 0;
	while (i < PATROL_BOAT_S * PATROL_BOAT_Q)
	{
		printf("\nChoose position for PATROL BOAT: ");
		scanf("%s", pos);
		printf("\n");
		user_map->map[pos[1] - 48][pos[0] - 97] = SHIP;
		printf("\e[1;1H\e[2J");
		print_single_map(user_map);
		i++;
	}
}

t_map *get_user_map()
{
	t_map *user_map;

	user_map = malloc(sizeof(t_map));
	if (user_map == NULL || errno)
		exit(0);
	user_map = allocate_memory(user_map);
	if (user_map == NULL)
		exit(0);
	user_map = initialize_empty_map(user_map);
	fill_user_map(user_map);
	return (user_map);
}

t_map *get_user_game_map()
{
	t_map *game_map;

	game_map = malloc(sizeof(t_map));
	if (game_map == NULL || errno)
		exit(0);
	game_map = allocate_memory(game_map);
	if (game_map == NULL)
		exit(0);
	game_map = initialize_empty_map(game_map);
	return (game_map);
}
