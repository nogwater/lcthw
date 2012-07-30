#include <stdio.h>

int main(int argc, char *argv[])
{
	// go through each string in argv

	int i = argc - 1;
	while(i >= 0) {
		printf("arg %d: %s\n", i , argv[i]);
		i--;
	}

	// let's make our own array of strings
	char *states[] = {
		"CA", "OR", "WA", "TX"
	};

	int num_states = 4;
	i = 0;
	while(i < num_states && i < argc) {
		states[i] = argv[i];
		printf("state %d: %s\n", i , states[i]);
		i++;
	}

	return 0;
}