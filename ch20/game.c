#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "game.h"

int Monster_attack(void *self, int damage)
{
	assert(self != NULL);
	assert(damage >= 0); // maybe we want to "attack" with a health spell? see underflow check below
	Monster *monster = self;

	printf("You attack %s!\n", monster->_(description));

	int new_hp = monster->hit_points - damage;
	assert(new_hp <= monster->hit_points); // underflow check
	monster->hit_points = new_hp; // nobody mention race conditions


	if (monster->hit_points > 0) {
		printf("It is still alive.\n");
		return 0;
	} else {
		printf("It is dead!\n");
		return 1;
	}
}

int Monster_init(void *self)
{
	assert(self != NULL);
	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};


void *Room_move(void *self, Direction direction)
{
	assert(self != NULL);
	Room *room = self;
	Room *next = NULL;

	if (direction == NORTH && room->north) {
		printf("You go north, into:\n");
		next = room->north;
	} else if (direction == SOUTH && room->south) {
		printf("You go south, into:\n");
		next = room->south;
	} else if (direction == EAST && room->east) {
		printf("You go east, into:\n");
		next = room->east;
	} else if (direction == WEST && room->west) {
		printf("You go west, into:\n");
		next = room->west;
	} else {
		printf("You can't go that direction.");
		next = NULL;
	}

	if (next) {
		next->proto.describe(next);
	}

	return next;
}


int Room_attack(void *self, int damage)
{
	assert(self != NULL);
	Room *room = self;
	Monster *monster = room->bad_guy;

	if (monster) {
		monster->proto.attack(monster, damage);
		return 1;
	} else {
		printf("You flail in the air at nothing. Idiot.\n");
		return 0;
	}
}


Object RoomProto = {
	.move = Room_move,
	.attack = Room_attack
};


void *Map_move(void *self, Direction direction)
{
	assert(self != NULL);
	Map *map = self;
	Room *location = map->location;
	assert(location != NULL);
	Room *next = NULL;

	next = location->proto.move(location, direction);

	if (next) {
		map->location = next;
	}

	return next; // may be NULL
}

int Map_attack(void *self, int damage)
{
	assert(self != NULL);
	// check for valid damanage is done elsewhere
	Map *map = self;
	Room *location = map->location;

	return location->proto.attack(location, damage);
}


int Map_init(void *self)
{
	assert(self != NULL);
	Map *map = self;

	Room *cell = Object_new(sizeof(Room), RoomProto, "An empty cell");
	assert(cell != NULL);

	map->start = cell;
	map->location = cell;

	return 1;
}

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};

int process_input(Map *game)
{
	assert(game != NULL);
	printf("\n> ");

	char ch = getchar();
	getchar(); // eat ENTER

	int damage = random() % 4;

	switch(ch)
	{
		case -1:
			printf("Giving up? You suck.\n");
			return 0;
			break;

		case 'n':
			game->proto.move(game, NORTH);
			break;
	
		case 's':
			game->proto.move(game, SOUTH);
			break;
			
		case 'e':
			game->proto.move(game, EAST);
			break;
			
		case 'w':
			game->proto.move(game, WEST);
			break;

		case 'a':
			game->proto.attack(game, damage);
			break;

		case 'l':
			printf("You can go:\n");
			if (game->location->north) printf("NORTH\n");
			if (game->location->south) printf("SOUTH\n");
			if (game->location->east) printf("EAST\n");
			if (game->location->west) printf("WEST\n");
			if (game->location->bad_guy) {
				// Object *monster_obj = (Object *obj)(game->location->bad_guy);
				// printf(monster_obj->description);
				if (game->location->bad_guy->hit_points > 0) {
					printf("Bad guy (%d)\n", game->location->bad_guy->hit_points);
				} else {
					printf("Bad guy (DEAD)\n");
				}
			}
			break;

		default:
			printf("What?: %d\n", ch);
	}

	return 1;
}

int game_loop(char *name, map_fill_cb map_filler)
{
	
	// simple way to setup the randomness
	srandom(time(NULL));

	// make our map to work iwth
	Map *map = NEW(Map, name);
	assert(map != NULL);
	printf("Welcome to \"%s\"\n", name);

	map_filler(map);

	printf("You enter the ");
	map->location->proto.describe(map->location);

	while(process_input(map)) {
	}

	return 0;
}