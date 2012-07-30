#include <stdio.h>
#include <assert.h>
#include <string.h>

struct Person {
	int age;
	int height;
	int weight;
	char name[256];
};

struct Person Person_create(char name[], int age, int height, int weight)
{
	struct Person who;

	int name_len = strlen(name);
	assert(name_len < 256);

	strcpy(who.name, name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

struct Person Person_age(struct Person who)
{
	who.age = who.age + 1;
	// structs passed by value need to be returned if you care about modifications
	return who;
}

void Person_print(struct Person who)
{
	printf("Name: %s\n", who.name);
	printf("\tAge:\t%d\n", who.age);
	printf("\tHeight:\t%d\n", who.height);
	printf("\tWeight:\t%d\n", who.weight);
}

int main(int argc, char *argv[])
{
	
	struct Person larry = Person_create("Larry Wall", 57, 60, 175);
	Person_print(larry);

	int i = 0;
	for (i = 0; i < 20; i++) {
		larry = Person_age(larry);
	}
	Person_print(larry);

	printf("sizeof(struct Person): %ld\n", sizeof(struct Person));
	// 268 (mostly the name, I'm sure)

	return 0;
}
