#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ERROR: You need at least one argument.\n");
		// this is how you abort a program
		return 1;
	}

	int a = 1;
	for (a = 1; a < argc; a++) {

		int i = 0;
		for (i = 0; argv[a][i] != '\0'; i++) {
			char letter = argv[a][i];
			// lowercase
			if (letter >= 'A' && letter <= 'Z') {
				letter = (letter - 'A') + 'a';
			}

			// if (letter == 'a') {
			// 	printf("%d: 'A'\n", i);
			// } else if (letter == 'e') {
			// 	printf("%d: 'E'\n", i);
			// } else if (letter == 'i') {
			// 	printf("%d: 'I'\n", i);
			// } else if (letter == 'o') {
			// 	printf("%d: 'O'\n", i);
			// } else if (letter == 'u') {
			// 	printf("%d: 'U'\n", i);
			// } else if (letter == 'y') {
			// 	if (i > 2) {
			// 		// it's only sometimes Y
			// 		printf("%d: 'Y'\n", i);
			// 	}
			// } else {
			// 	printf("%d: %c is not a vowel\n", i, letter);
			// }

			switch (letter) {
				case 'a':
				// case 'A':
					printf("%d: 'A'\n", i);
					break;
				case 'e':
				// case 'E':
					printf("%d: 'E'\n", i);
					break;
				case 'i':
				// case 'I':
					printf("%d: 'I'\n", i);
					break;
				case 'o':
				// case 'O':
					printf("%d: 'O'\n", i);
					break;
				case 'u':
				// case 'U':
					printf("%d: 'U'\n", i);
					break;
				case 'y':
				// case 'Y':
					if (i > 2) {
						// it's only sometimes Y
						printf("%d: 'Y'\n", i);
						break;
					}
				default:
					printf("%d: %c is not a vowel\n", i, letter);
			}
		}
	}

	return 0;
}