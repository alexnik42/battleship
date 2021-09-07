#include "b_header.h"

t_map *allocate_memory(t_map *map)
{
	int i;

	map->height = BATTLEFIELD_SIZE;
	map->width = BATTLEFIELD_SIZE;
	map->battlefield = malloc(sizeof(char *) * map->height);
	if (map->battlefield == NULL || errno)
	{
		free_map(map);
		return (NULL);
	}
	i = 0;
	while (i < map->height)
	{
		map->battlefield[i] = malloc(sizeof(char) * (map->width + 1));
		if (map->battlefield[i] == NULL)
		{
			free_battlefield(map->battlefield, i);
			free_map(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

t_map *initialize_empty_map(t_map *map, t_ships *ships)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			map->battlefield[i][j++] = EMPTY;
		i++;
	}
	map->ships_units_left = 0;
	k = 0;
	while (k < NUMBER_OF_SHIPS)
		map->ships_units_left += ships[k++].size;
	return (map);
}

t_map *create_new_map(t_map *map, t_ships *ships)
{
	map = allocate_memory(map);
	if (map == NULL)
		return (NULL);
	map = initialize_empty_map(map, ships);
	if (map == NULL)
		return (NULL);
	return (map);
}
