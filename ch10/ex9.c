#include <stdio.h>

int main(int argc, char *argv[])
{
	int numbers[4] = {0};
	char name[4] = {'a', 'a', 'a', 'a'};

	// first, print them out raw
	printf("numbers: %d %d %d %d\n",
		numbers[0], numbers[1],
		numbers[2], numbers[3]);
	
	printf("name each: %c %c %c %c\n",
		name[0], name[1],
		name[2], name[3]);

	// setup the numbers
	numbers[0] = 1;
	numbers[1] = 'b';
	numbers[2] = 3;
	numbers[3] = 4;

	// setup the name
	name[0] = 'Z';
	name[1] = 72;
	name[2] = 'd';
	name[3] = 'A';

	// the print them out initialized
	printf("numbers: %d %d %d %d\n",
		numbers[0], numbers[1],
		numbers[2], numbers[3]);
	
	printf("name each: %c %c %c %c\n",
		name[0], name[1],
		name[2], name[3]);
	
	// print the name like a string
	printf("name: %s\n", name);

	// another way to use name
	char *another = "Zed";

	printf("another: %s\n", another);

	printf("another each: %c %c %c %c\n", 
		another[0], another[1], another[2], another[3]);

	char crazy_int[4] = "\0\0\0\0";
	crazy_int[0] = 1;
	crazy_int[1] = 2;
	crazy_int[2] = 3;
	crazy_int[3] = 4;
	int int_crazy = (int)*crazy_int;
	printf("crazy_int: %d\n", int_crazy);

	return 0;
}