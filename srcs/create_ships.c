#include "b_header.h"

t_ships *create_ships(void)
{
	t_ships *ships;

	ships = malloc(sizeof(t_ships) * NUMBER_OF_SHIPS);
	if (ships == NULL || errno)
		return (NULL);
	ships[0] = (t_ships){.name = CARRIER_NAME, .size = CARRIER_SIZE};
	ships[1] = (t_ships){.name = BATTLESHIP_NAME, .size = BATTLESHIP_SIZE};
	ships[2] = (t_ships){.name = DESTROYER_NAME, .size = DESTROYER_SIZE};
	ships[3] = (t_ships){.name = SUBMARINE_NAME, .size = SUBMARINE_SIZE};
	ships[4] = (t_ships){.name = PATROL_BOAT_NAME, .size = PATROL_BOAT_SIZE};
	return (ships);
}
