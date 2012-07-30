// bring in some standard function (definitions) like printf
#include <stdio.h>
// bring in the assert macro (yep, macro... who knew?)
#include <assert.h>
// bring in the memory stuff (malloc, free)
#include <stdlib.h>
// bring in strdup
#include <string.h>

// create a struct type (not an actual object) called "struct Person"
struct Person {
	// the struct Person type has-a name (pointer to a char (string))
	char *name;
	// also an age
	int age;
	// BTW: I think the memory layout is all manual
	int height;
	// so be careful!
	int weight;
// Done with the struct definition (don't forget the semicolon!!!)
};

// define a function that will return a pointer to a struct Person, given some info
struct Person *Person_create(char *name, int age, int height, int weight)
{
	// try get enough memory for a struct Person object
	// if it works, save the memory address in the who pointer
	struct Person *who = malloc(sizeof(struct Person));
	// if (unimaginable on this computer) we didn't have enough memory, 
	// then who would be NULL (0?).
	// we could confirm that that's what went wrong by checking errno for ENOMEM
	assert(who != NULL); // Out of memory?

	// make a new copy of the name in memory, and save this memory location in  the who->name pointer
	who->name = strdup(name);
	// copy more info about the user
	who->age = age;
	// such has height
	who->height = height;
	// and weight
	who->weight = weight;

	// return the pointer to this new person
	return who;
}

// if we can create people, we should also destroy them (no auto-memory management... well kill the process)
void Person_destroy(struct Person *who)
{
	// just a good idea to test this, I bet free wouldn't eat the computer if you did free(NULL)
	// it looks like free(NULL) does nothing, but it's still a good idea to check
	// besides, I bet that member access wouldn't work so well on NULL
	assert(who != NULL);

	// remember! we allocated our own memory for the name, so we have to manually clean it up
	free(who->name);
	// finally free the memory for the who struct Person object
	free(who);
	// hopefully nothing tries to use who after this
}

// A simple print function. not really worth describing
void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	// make two people structures
	struct Person *joe = Person_create(
		"Joe Alex", 32, 64, 140);
	
	struct Person *frank = Person_create(
		"Frank Black", 20, 72, 180);
	
	// print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);

	printf("A person takes up %ld bytes of RAM\n", sizeof(struct Person));

	// make everyone age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	// assert(joe->weight < 150);

	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);

	// Person_print(NULL); // to break it

	// destroy them both so we clean up
	Person_destroy(joe);
	Person_destroy(frank);
	// Person_destroy(NULL); // to break it

	return 0;
}