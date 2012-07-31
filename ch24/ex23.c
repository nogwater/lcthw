#include <stdio.h>
#include <string.h>
#include "dbg.h"


int normal_copy(char *from, char *to, int count)
{
	int i =  0;

	for (i = 0; i < count; i++) {
		to[i] = from[i];
	}

	return i;
}

int valid_copy(char *data, int count, char expects)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		if (data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}

	return 1;
}


int main(int argc, char *argv[])
{
	char from[1000] = {'a'};
	char to[1000] = {'c'};
	int rc = 0;

	// setup the from to have some stuff
	memset(from, 'x', 1000);
	// set it to a failure mode
	memset(to, 'y', 1000);
	check(valid_copy(to, 1000, 'y'), "Not initialized right.");

	// use normal copy to
	rc = normal_copy(from, to, 1000);
	check(rc == 1000, "Normal copy failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Normal copy failed.");

	return 0;
error:
	return 1;
}