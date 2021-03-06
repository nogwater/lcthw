#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE_EYES, GREEN_EYES, BROWN_EYES,
	BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

// reads from standard input and writes to str
// reads at most size-1 chars from stdin (need space for \0)
// stops at \n
void readline(char *str, int size)
{
	int i = 0;
	unsigned char ch;

	if (size > 0) {
		scanf("%c", &ch);
		while (i < size-1 && ch != '\n') {
			str[i] = ch;
			scanf("%c", &ch);
			i++;
		}
	}
	str[i] = '\0';
}

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i = 0; int rc = 0;
	// char *in = NULL;
	// char temp[MAX_DATA];

	printf("What's your First Name? ");
	// in = fgets(you.first_name, MAX_DATA-1, stdin);	// NOTE: this includes the trailing new-line
	// Warning: if a user enters more than MAX_DATA-1, the rest will be sent to the next input (not really a good solution)
	// check(in != NULL, "Failed to read first name.", NULL);
	// rc = fscanf(stdin, "%50s", you.first_name);	// fscanf is bad for strings
	// check(rc > 0, "You have to enter a first name.");
	// in = gets(you.first_name);  // WARNING: will read too much! Very Bad! Never use gets()
	// check(in != NULL, "Failed to read first name.");
	readline((char *)&you.first_name, MAX_DATA);

	printf("What's your Last Name? ");
	// in = fgets(you.last_name, MAX_DATA-1, stdin);	// NOTE: this includes the trailing new-line
	// check(in != NULL, "Failed to read last name.", NULL);
	readline((char *)&you.last_name, MAX_DATA);

	printf("How old are you? ");
	rc = fscanf(stdin, "%d", &you.age);
	check(rc > 0, "You have to enter a number.", NULL);
	// in = fgets(temp, MAX_DATA-1, stdin);
	// check(in != NULL, "Failed to read age.");
	// you.age = atoi(temp);

	printf("What color are your eyes:\n");
	for (i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	check(rc > 0, "You have to enter a number.");
	// in = fgets(temp, MAX_DATA-1, stdin);
	// check(in != NULL, "Failed to read eyes option.", NULL);
	// eyes = atoi(temp);
	// log_info("temp: %s, eyes: %d", temp, eyes);

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.", NULL);

	printf("How much do you make an hour? ");
	rc = fscanf(stdin, "%f", &you.income);
	check(rc > 0, "Enter a floating point number.");
	// in = fgets(temp, MAX_DATA-1, stdin);
	// check(in != NULL, "Failed to read income.", NULL);
	// you.income = atof(temp);

	printf("----- RESULTS -----\n");

	printf("First Name: %s\n", you.first_name);
	printf("Last Name: %s\n", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	return 0;
error:

	return -1;
}
