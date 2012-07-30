#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	for (i = 0; i < argc; i++) {
		int j = 0;
		while (argv[i][j] != '\0') {
			int letter = argv[i][j];
			if (letter >= 'A' && letter <= 'Z') {
				letter = (letter - 'A') + 'a';
			}
			printf("%c", letter);
			j++;
		}
		printf("\n");
	}

	return 0;
}
