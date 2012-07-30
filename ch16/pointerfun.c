#include <stdio.h>

void print_arg(char *arg)
{
	printf("%s\n", arg);
}

int main(int argc, char *argv[])
{
	int i = 0;
	
	// print args with fun
	// for (i = 0; i < argc; i++) {
	// 	print_arg(argv[i]);
	// }

	// print args like crazy
	// for (i = 0; i < 1024*1024; i++) {
	for (i = 0; i < 32; i++) {
		//char ch = *((argv[0]) + i);
		char ch = *(*argv + i);
		if (ch == '\0') {
			printf(" ");
		} else {
			printf("%c", ch);
		}
	}
	// for (i = 32; i > -(1024*1024); i--) {
	// 	printf("%c", *((*argv) + i));
	// }

	printf("\n\n");


	// print the args using a pointer (destructive because it changes argc and argv)
	// while (argc--) {
	// 	printf("address of argv:   %p\n", &argv);
	// 	printf("address of *argv:  %p\n", &(*argv));
	// 	printf("address of **argv:  %p\n", &(**argv));
	// 	printf("%s\n", *(argv++));
	// }




	return 0;
}