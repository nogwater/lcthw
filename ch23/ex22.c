#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
	return THE_AGE;
}

void set_age(int age)
{
	THE_AGE = age;
}


double update_ratio(double new_ratio)
{
	static double ratio = 1.0;

	double old_ratio = ratio;
	ratio = new_ratio;

	return old_ratio;
}

double double_pointer(double *new_ptr)
{
	static double *ptr = NULL;
	if (new_ptr != NULL)
	{
		ptr = new_ptr;
	}
	if (ptr != NULL)
	{
		return 2.0 * *ptr;
	}
	return 0.0;
}

void print_size()
{
	log_info("I think size is: %d", THE_SIZE);
}
