#include <stdio.h>

int main(int argc, char *argv[])
{
	int areas[] = {10, 72, 13, 14, 20};
	char name[] = "Zed\0asdf";
	char full_name[] = {
		'Z', 'e', 'd',
		' ', 'A', '.', ' ',
		'S', 'h', 'a', 'w', '\0'
	};

	areas[0] = 99;
	name[1] = areas[1];
	full_name[1] = name[1];

	// WARNING: On some systems you may have to change the
	// %ld in this code to a %u since it will use unsigned ints
	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n",
		sizeof(areas));
	printf("The first area is %d, the 2nd %d\n", 
		areas[0], areas[1]);
	printf("The first area size is %ld, the 2nd %ld\n", 
		sizeof(areas[0]), sizeof(areas[1]));
	
	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name (char[]): %ld\n",
		sizeof(name));
	printf("The number of chars: %ld\n",
		(sizeof(name) / sizeof(char)));
	
	printf("name=\"%s\" and full_name=\"%s\"\n",
		name, full_name);

	return 0;
}