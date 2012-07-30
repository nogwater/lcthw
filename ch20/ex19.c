#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"

extern Object MonsterProto;
extern Object RoomProto;
extern Object MapProto;

void minotaur_filler(Map *map)
{
	assert(map != NULL);

	// make some rooms for a small map
	// Room *hall = NEW(Room, "The great Hall");
	// Room *throne = NEW(Room, "The throne room");
	// Room *arena = NEW(Room, "The arena, with the minotaur.");
	// Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
	Room *hall = Object_new(sizeof(Room), RoomProto, "The great Hall");
	Room *throne = Object_new(sizeof(Room), RoomProto, "The throne room");
	Room *arena = Object_new(sizeof(Room), RoomProto, "The arena, with the minotaur.");
	Room *kitchen = Object_new(sizeof(Room), RoomProto, "Kitchen, you have the knife now");
	Room *bath = Object_new(sizeof(Room), RoomProto, "The other throne room");
	assert(hall != NULL);
	assert(throne != NULL);
	assert(arena != NULL);
	assert(kitchen != NULL);
	assert(bath != NULL);

	// the the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");
	assert(arena->bad_guy != NULL);

	// setup the map rooms
	hall->north = throne;

	throne->north = bath;
	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	bath->south = throne;

	arena->east = throne;
	kitchen->west = throne;

	// start the map and the character off in the hall
	map->start = hall;
	map->location = hall;
}

void crazy_filler(Map *map)
{
	assert(map != NULL);

	// make some rooms for a small map
	Room *roomA = NEW(Room, "Room A");
	Room *roomB = NEW(Room, "Room B");
	Room *roomC = NEW(Room, "Room C");
	Room *roomD = NEW(Room, "Room D");
	assert(roomA != NULL);
	assert(roomB != NULL);
	assert(roomC != NULL);
	assert(roomD != NULL);

	// the the bad guy in each room
	roomA->bad_guy = NEW(Monster, "The evil minotaur of A");
	assert(roomA->bad_guy != NULL);
	roomB->bad_guy = NEW(Monster, "The evil minotaur of B");
	assert(roomB->bad_guy != NULL);
	roomC->bad_guy = NEW(Monster, "The evil minotaur of C");
	assert(roomC->bad_guy != NULL);
	roomD->bad_guy = NEW(Monster, "The evil minotaur of D");
	assert(roomD->bad_guy != NULL);

	// setup the map rooms
	roomA->east = roomB;
	roomA->south = roomC;

	roomB->west = roomA;
	roomB->south = roomD;

	roomC->north = roomA;
	roomC->east = roomD;

	roomD->north = roomB;
	roomD->west = roomC;

	// start the map and the character off in the hall
	map->start = roomA;
	map->location = roomA;
}

int main(int argc, char *argv[])
{
	// return game_loop("The Hall of the Minotaur.", minotaur_filler);
	return game_loop("Crazy Map of Craze", crazy_filler);
}
