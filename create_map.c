#include "b_header.h"

t_map *allocate_memory(t_map *map)
{
	int i;

	map->height = MAP_SIZE;
	map->width = MAP_SIZE;
	map->map = malloc(sizeof(char *) * map->height);
	if (map->map == NULL || errno)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		if (map->map[i] == NULL)
			return (NULL);
		i++;
	}
	map->ships = malloc(sizeof(t_ships));
	if (map->ships == NULL || errno)
		return (NULL);
	return (map);
}

t_map *initialize_empty_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			map->map[i][j++] = EMPTY;
		i++;
	}
	map->ships->carrier = CARRIER_Q;
	map->ships->battleship = BATTLESHIP_Q;
	map->ships->destroyer = DESTROYER_Q;
	map->ships->submarine = SUBMARINE_Q;
	map->ships->patrol_boat = PATROL_BOAT_Q;
	map->total_ships_size = (CARRIER_Q * CARRIER_S + BATTLESHIP_Q * BATTLESHIP_S + DESTROYER_Q * DESTROYER_S + SUBMARINE_Q * SUBMARINE_S + PATROL_BOAT_Q * PATROL_BOAT_S);
	return (map);
}
