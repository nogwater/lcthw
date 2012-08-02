#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "dbg.h"

#define CASES_0_7_1(code) again: case 0:code; case 7:code; case 6:code; case 5:code; case 4:code; case 3:code; case 2:code; case 1:code; 

int normal_copy(char *from, char *to, int count)
{
	int i =  0;

	for (i = 0; i < count; i++) {
		to[i] = from[i];
	}

	return i;
}

int duffs_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch (count % 8) {
			case 0: do { *to++ = *from++;
						case 7: *to++ = *from++;
						case 6: *to++ = *from++;
						case 5: *to++ = *from++;
						case 4: *to++ = *from++;
						case 3: *to++ = *from++;
						case 2: *to++ = *from++;
						case 1: *to++ = *from++;
					} while(--n > 0);
		}
	}

	return count;
}

int zeds_device(char *from, char *to, int count)
{
	// {  // why did Zed add this block level?
		int n = (count + 7) / 8;

		switch(count % 8) {
			case 0:
			again: *to++ = *from++;

			case 7: *to++ = *from++;
			case 6: *to++ = *from++;
			case 5: *to++ = *from++;
			case 4: *to++ = *from++;
			case 3: *to++ = *from++;
			case 2: *to++ = *from++;
			case 1: *to++ = *from++;
					if (--n > 0) goto again;
		}
	// }

	return count;
}


int zeds_short_device(char *from, char *to, int count)
{
	int n = (count + 7) / 8;

	switch(count % 8) {
		CASES_0_7_1(*to++ = *from++)
		if (--n > 0) goto again;
	}

	return count;
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

double time_it(int(*copier)(char *, char *, int), int count)
{
	struct timeval tvBegin, tvEnd;
	char from[10000] = {'a'};
	char to[10000] = {'c'};

	int i = 0;

	gettimeofday(&tvBegin, NULL);
	for (i = 0; i < count; i++) {
		copier(from, to, 10000);
	}
	gettimeofday(&tvEnd, NULL);

	return (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000000.0);
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

	// reset
	memset(to, 'y', 1000);

	// duffs version
	rc = duffs_device(from, to, 1000);
	check(rc == 1000, "Duff's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Duff's device failed.");

	// reset
	memset(to, 'y', 1000);

	// zed's version
	rc = zeds_device(from, to, 1000);
	check(rc == 1000, "Zed's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Zed's device failed.");

	// zed's extra credit version
	rc = zeds_short_device(from, to, 1000);
	check(rc == 1000, "Zed's short device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Zed's short device failed.");

	// reset
	memset(to, 'y', 1000);

	// time some stuff (try this with and without -O3 in Makefile)
	log_info("Time to run normal_copy: %.5f", time_it(normal_copy, 10000));
	log_info("Time to run duffs_device: %.5f", time_it(duffs_device, 10000));
	log_info("Time to run zeds_device: %.5f", time_it(zeds_device, 10000));
	log_info("Time to run zeds_short_device: %.5f", time_it(zeds_short_device, 10000));


	return 0;
error:
	return 1;
}