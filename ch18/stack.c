#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000


struct Stack
{
	int data[STACK_SIZE];
	int next;
};

struct Stack *Stack_create()
{
	return malloc(sizeof(struct Stack));
}

void Stack_destory(struct Stack *stk)
{
	free(stk);
}

void Stack_push(struct Stack *stk, int element)
{
	if (stk->next < STACK_SIZE - 1) {
		stk->data[stk->next] = element;
		stk->next += 1;
	} else {
		printf("STACK OVERFLOW!!!\n");
	}
}

int Stack_pop(struct Stack *stk)
{
	int ret = 0;

	if (stk->next > 0) {
		stk->next -= 1;
		ret = stk->data[stk->next];
	} else {
		printf("STACK UNDERFLOW!!!\n");
	}

	return ret;
}


int main(int argc, char *argv[])
{
	int x = 0;

	struct Stack *stk1 = Stack_create();

	printf("pop!\n");
	x = Stack_pop(stk1);

	printf("push 1\n");
	Stack_push(stk1, 1);
	printf("push 2\n");
	Stack_push(stk1, 2);
	printf("push 3\n");
	Stack_push(stk1, 3);


	printf("popped: %d\n", Stack_pop(stk1));
	printf("popped: %d\n", Stack_pop(stk1));

	printf("push 20\n");
	Stack_push(stk1, 20);
	printf("push 30\n");
	Stack_push(stk1, 30);


	printf("popped: %d\n", Stack_pop(stk1));
	printf("popped: %d\n", Stack_pop(stk1));
	printf("popped: %d\n", Stack_pop(stk1));
	printf("popped: %d\n", Stack_pop(stk1));
	printf("popped: %d\n", Stack_pop(stk1));

	Stack_destory(stk1);
	
	return 0;
}