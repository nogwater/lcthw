#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
	log_info("count is: %d", count);

	if (count > 10) {
		int count = 100; // BAD! BUGS!

		log_info("count in this scope is %d", count);
	}

	log_info("count is at exit: %d", count);

	count = 3000;

	log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
	// tst out THE_AGE accessors
	log_info("My name: %s, age: %d", MY_NAME, get_age());

	set_age(100);

	log_info("My age is now: %d", get_age());

	// test out THE_SIZE extern
	log_info("THE_SIZE is: %d", THE_SIZE);
	print_size();

	THE_SIZE = 9;

	log_info("THE_SIZE is: %d", THE_SIZE);
	print_size();

	// test the ratio function static
	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio again: %f", update_ratio(10.0));
	log_info("Ratio once more: %f", update_ratio(300.0));

	// test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("count after calling scope_demo: %d", count);

	// try to break it
	// ratio = 2.5; // error: 'ratio' undeclared (first use in this function)
	// log_info("Ratio is now: %f", ratio);
	log_info("Weird double: %f", double_pointer(NULL));
	double d = 2.0;
	double *ptr = &d;
	log_info("Weird double: %f", double_pointer(ptr));
	d = 10.0;
	log_info("Weird double: %f", double_pointer(NULL));

	return 0;
}
