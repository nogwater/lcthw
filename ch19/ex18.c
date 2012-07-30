#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

// a typedef creates a fake type, 
// in this case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int * (*sort_cb)(int *numbers, int count, compare_cb cmp);

void print_numbers(char *msg, int *numbers, int count)
{
	int i = 0;
	
	printf("%s", msg);
	for (i = 0; i < count; i++) {
		printf("%d ", numbers[i]);
	}
	printf("\n");	
}

void swap_numbers(int *numbers, int i, int j)
{
	int temp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = temp;
}

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.   NOT IN PLACE!!
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if(!target) die("Memory error.");
	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i < count; i++) {
		for(j = 0; j < count - 1; j++) {
			if (cmp(target[j], target[j+1]) > 0) {
				swap_numbers(target, j, j+1);
			}
		}
	}

	return target;
}

// http://www.algorithmist.com/index.php/Quicksort#Pseudocode
int qs_partition(int *numbers, int low, int high, compare_cb cmp)
{
	int pivot = numbers[low];
	int leftwall = low;
	int i = 0;

	for (i = low + 1; i <= high; i++) {
		if (cmp(numbers[i], pivot) < 0) {
			leftwall = leftwall + 1;
			swap_numbers(numbers, i, leftwall);
		}
	}

	swap_numbers(numbers, low, leftwall);

	return leftwall;
}
// in place
void quick_sort_body(int *numbers, int low, int high, compare_cb cmp)
{
	int pivot_location = 0;
	if (low < high) {
		pivot_location = qs_partition(numbers, low, high, cmp);
		quick_sort_body(numbers, low, pivot_location - 1, cmp);
		quick_sort_body(numbers, pivot_location + 1, high, cmp);
	}
}



// makes a copy
int *quick_sort(int *numbers, int count, compare_cb cmp)
{
	int *target = malloc(count * sizeof(int));
	if(!target) die("Memory error.");
	memcpy(target, numbers, count * sizeof(int));

	quick_sort_body(target, 0, count-1, cmp);

	return target;
}



int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}

/**
 * Used  to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp, sort_cb srt)
{
	int *sorted = srt(numbers, count, cmp);

	if (!sorted) die("Failed to sort as requested.");

	print_numbers("sorted: ", sorted, count);

	free(sorted);

	// int i = 0;
	// unsigned char *data = (unsigned char *)cmp;
	// for (i = 0; i < 25; i++) {
	// 	printf("%0x:", data[i]);
	// }
	// printf("\n");
}


int main(int argc, char *argv[])
{
	if (argc < 2) die("Usage: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	printf("Forward with bubble_sort and quick_sort.\n");
	test_sorting(numbers, count, sorted_order, bubble_sort);
	test_sorting(numbers, count, sorted_order, quick_sort);

	printf("Backward with bubble_sort and quick_sort.\n");
	test_sorting(numbers, count, reverse_order, quick_sort);
	test_sorting(numbers, count, reverse_order, bubble_sort);

	// printf("Strange with bubble_sort and quick_sort.\n");
	// test_sorting(numbers, count, strange_order, quick_sort);
	// test_sorting(numbers, count, strange_order, bubble_sort);
	
	free(numbers);

	return 0;
}
































































