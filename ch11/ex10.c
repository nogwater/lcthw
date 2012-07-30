#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	int num_states = 5;

	// let's make our own array of strings
	char *states[] = {
		"California", "Oregon",
		"Washington", NULL, "Texas"
	};

	// mix things up a bit
	states[4] = argv[0];
	argv[0] = states[0];

	// go through each string in argv
	// why am I skipping arg[0]?
	for (i = 0; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}
	
	printf("\n");

	for (i = 0; i < num_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	/*
	array of strings
		[
			[California]
			[Oregon]
			[Washington]
			[Texas]
		]
	*/
	
	return 0;
}