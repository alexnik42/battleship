#include "b_header.h"

void print_color(char c)
{
	if (c == MISS)
		printf(YEL "%c" RESET, c);
	else if (c == HIT)
		printf(RED "%c" RESET, c);
	else if (c == SHIP)
		printf(GRN "%c" RESET, c);
	else
		printf(MAG "%c" RESET, c);
}

void print_user_map(t_map *user_map)
{
	int i;
	int j;

	i = 0;
	printf("\n<<<<< WELCOME TO BATTLESHIP GAME >>>>>\n\n");
	printf("    A  B  C  D  E  F  G  H  I  J\n");
	printf("   _____________________________\n");
	while (i < user_map->height)
	{
		j = 0;
		printf("%d | ", i);
		while (j < user_map->width)
		{
			print_color(user_map->battlefield[i][j]);
			if (j != user_map->width - 1)
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void print_computer_map(t_map *computer_map)
{
	int i;
	int j;

	i = 0;
	printf("           OPPONENT'S MAP       \n");
	printf("    A  B  C  D  E  F  G  H  I  J\n");
	printf("   _____________________________\n");
	while (i < computer_map->height)
	{
		j = 0;
		printf("%d | ", i);
		while (j < computer_map->width)
		{
			print_color(computer_map->battlefield[i][j]);
			if (j != computer_map->width - 1)
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void print_game_maps(t_map *user_map, t_map *game_map)
{
	int i;
	int j;

	i = 0;
	printf("\n<<<<<<<<<<<<<<<<<<<< WELCOME TO BATTLESHIP GAME >>>>>>>>>>>>>>>>>>>>\n\n");
	printf("             YOUR MAP                             OPPONENT'S MAP       \n");
	printf("    A  B  C  D  E  F  G  H  I  J           A  B  C  D  E  F  G  H  I  J\n");
	printf("   _____________________________          _____________________________\n");
	while (i < user_map->height)
	{
		j = 0;
		printf("%d | ", i);
		while (j < user_map->width)
		{
			print_color(user_map->battlefield[i][j]);
			if (j != user_map->width - 1)
				printf("  ");
			j++;
		}
		printf("       ");
		j = 0;
		printf("%d | ", i);
		while (j < game_map->width)
		{
			print_color(game_map->battlefield[i][j]);
			if (j != game_map->width - 1)
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}
