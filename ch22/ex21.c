#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


void showDataTypes()
{
	// Standard Data Types
	int i = 2000000000;
	double d = 987654321.0123456789;
	float f = 0.123456789f;
	char c = 'a';
	void *vp = NULL;
	enum cardsuit {
		CLUBS,
		DIAMONDS,
		HEARTS,
		SPADES, // trailing comma is bad	
	};

	printf("\nData types:\n");
	printf("i is an int with value %d and uses %ld bytes.\n", i, sizeof i);
	printf("d is a double with value %f and uses %ld bytes.\n", d, sizeof d);
	printf("f is a float with value %f and uses %ld bytes.\n", f, sizeof f);
	printf("c is a char with value %c and uses %ld byte.\n", c, sizeof c);
	printf("vp is a void * with address %p and uses %ld bytes.\n", vp, sizeof vp);

	// Type Modifiers
	unsigned int ui = 4000000000;
	signed char sc = -100;
	long int li = -4000000000;
	short int si = -32000;

	printf("\nType Modifiers:\n");
	printf("ui is an unsigned int with value %u and uses %ld bytes.\n", ui, sizeof ui);
	printf("sc is a signed char with value %d and uses %ld byte.\n", sc, sizeof sc);
	printf("li is a long int with value %ld and uses %ld bytes.\n", li, sizeof li);
	printf("si is a short int with value %d and uses %ld bytes.\n", si, sizeof si);

	// Type Qualifiers
	const int AGE = 34; // I will be 34 forever
	volatile int v = 2;
	register int r = 20;

	printf("\nType Qualifiers:\n");
	// AGE = 35; // FAILS
	printf("'const' makes it so that the variable can't be changed. AGE=%d\n", AGE);
	printf("'volatile' tells the compiler that this variable may change at any time. v=%d\n", v);
	printf("'register' asks the compiler to store this variable in a register. r=%d\n", r);

	printf("\nType Conversion:\n");
	c = 'a';
	i = 1000;
	printf("Adding a char and an int gets you an int: %d (%ldb) + %d (%ldb) = %d (%ldb)\n", 
		c, sizeof c, i, sizeof i, (c + i), sizeof (c + i));
	printf("You can also force the matter with type casting: %d, %f\n", i, (double)i);

	// Type Sizes
	printf("\nType Sizes:\n");
	printf("stdint.h defines a bunch of typedefs and macros for specifc sized integer types.\n");
	int8_t i8 = -100;
	int64_t i64 = -4000000000;

	printf("inttypes.h defines macros for format specifiers for the stdint types.\n");
	// see http://www.nongnu.org/avr-libc/user-manual/group__avr__inttypes.html
	printf("i8 is a signed (at least) 8-bit integer with value %" PRId8 "\n", i8);
	printf("i64 is a signed (at least) 64-bit integer with value %" PRId64 "\n", i64);

	printf("a 8-bit int can hold numbers between %d and %d.\n", INT8_MIN, INT8_MAX);
	printf("a 16-bit int can hold numbers between %d and %d.\n", INT16_MIN, INT16_MAX);
	printf("a 32-bit int can hold numbers between %d and %d.\n", INT32_MIN, INT32_MAX);
	printf("a 64-bit int can hold numbers between %lld and %lld.\n", INT64_MIN, INT64_MAX);
	printf("a size_t can hold numbers up to %llu or %p.\n", SIZE_MAX, (void *)SIZE_MAX);
}


// TODO: Operators
// TODO: Control Structures



int main(int argc, char *argv[])
{
	printf("A bunch of samples of using C.\n");

	showDataTypes();




	return 0;
}