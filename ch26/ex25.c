/** WARNING: This code is fresh and potentially isn't correct yet. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	check_mem(*out_string);

	char *result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input error.");

	return 0;

error:
	if (*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_int(int *out_int)
{
	char *input = NULL;
	int rc = read_string(&input, MAX_DATA);
	check(rc == 0, "Failed to read number.");

	*out_int = atoi(input);

	free(input);
	return 0;

error:
	if (input) free(input);
	return -1;
}

int read_scan(const char *fmt, ...)
{
	int i = 0;
	int rc = 0;
	int *out_int = NULL;
	char *out_char = NULL;
	char **out_string = NULL;
	int max_buffer = 0;

	va_list argp;
	va_start(argp, fmt);

	for (i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

				case 'd':
					out_int = va_arg(argp, int *);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;

				case 'c':
					out_char = va_arg(argp, char *);
					*out_char = fgetc(stdin);
					break;

				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char **);
					rc = read_string(out_string, max_buffer);
					check(rc == 0, "Failed to read stirng.");
					break;

				default:
					sentinel("Invalid format.");
			}
		} else {
			fgetc(stdin);
		}

		check(!feof(stdin) && !ferror(stdin), "Input error.");
	}

	va_end(argp);
	return 0;

error:
	va_end(argp);
	return -1;
}

void print_int(int a)
{
	int neg = 0;
	char digits[9];
	int i = 0;

	if (a < 0) {
		neg = 1;
		a *= -1;
	}

	do {
		digits[i++] = '0' + (a % 10);
		a /= 10;
	} while (a != 0);


	if (neg == 1) {
		putchar('-');
	}

	for ( ; i >= 0; i--) {
		putchar(digits[i]);
	}
}

void print_str(const char *str)
{
	int i = 0;
	while (str[i] != '\0') {
		putchar(str[i]);
	}
}

int print_format(const char *fmt, ...)
{
	int i = 0;
	int in_int = 0;
	int in_char = 0;
	char *in_str = NULL;

	va_list argp;
	va_start(argp, fmt);

	for (i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

				case 'd':
					in_int = va_arg(argp, int);
					print_int(in_int);
					break;

				case 'c':
					in_char = va_arg(argp, int);
					putchar(in_char);
					break;

				case 's':
					in_str = va_arg(argp, char *);
					print_str(in_str);
					break;

				default:
					sentinel("Invalid format.");
			}
		} else {
			putchar(fmt[i]);
		}
	}

	va_end(argp);
	return 0;

error:
	va_end(argp);
	return -1;
}

int main(int argc, char *argv[])
{
	char *first_name = NULL;
	char initial = ' ';
	char *last_name = NULL;
	int age = 0;

	// break it!
	// read_scan("%s", 1000, 12345);// Segmentation fault: 11
	// read_scan("%s", 3, &first_name);
	print_format("Hello World!\n");

	printf("What's your first name? ");
	int rc = read_scan("%s", MAX_DATA, &first_name);
	check(rc == 0, "Failed first name.");

	printf("What's your initial? ");
	rc = read_scan("%c\n", &initial);
	check(rc == 0, "Failed initial.");

	printf("What's your last name? ");
	rc = read_scan("%s", MAX_DATA, &last_name);
	check(rc == 0, "Failed last name.");

	printf("How old are you? ");
	rc = read_scan("%d", &age);

	printf("---- RESULTS ----\n");
	printf("First Name: %s", first_name);
	printf("Initial: '%c'\n", initial);
	printf("Last Name: %s", last_name);
	print_format("Age: %d\n", age);

	free(first_name);
	free(last_name);
	return 0;
error:
	return -1;
}
