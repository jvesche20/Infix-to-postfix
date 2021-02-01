#include<stdio.h>
#include<stdlib.h>

struct stackNode {
	char data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int precedence(char operator1, char operator2) {
	int newOperator1, newOperator2;
	if (operator1 == '^') {
		newOperator1 = 3;
	}
	else if (operator1 == '*' || operator1 == '/' || operator1 == '%') {
		newOperator1 = 2;
	}
	else {
		newOperator1 = 1;
	}

	if (operator2 == '^') {
		newOperator2 = 3;
	}
	else if (operator2 == '*' || operator2 == '/' || operator2 == '%') {
		newOperator2 = 2;
	}
	else {
		newOperator2 = 1;
	}

	if (newOperator1 == newOperator2) return 0;
	if (newOperator1 - newOperator2 > 0) return 1;
	return -1;
}

void push(StackNodePtr *topPtr, char value) {
	StackNodePtr temp;
	temp = malloc(sizeof(StackNode));
	temp->data = value;
	temp->nextPtr = *topPtr;
	*topPtr = temp;
}
char pop(StackNodePtr *topPtr) {
	char c = (*topPtr)->data;
	(*topPtr) = (*topPtr)->nextPtr;
	return c;
}
void printStack(StackNodePtr topPtr) {
	StackNodePtr temp = topPtr;
	while (temp != NULL) {
		printf("%c ", temp->data);
		temp = temp->nextPtr;
	}
	printf("\n");
}
int isEmpty(StackNodePtr topPtr) {
	return (topPtr == NULL);
}
char stackTop(StackNodePtr topPtr) {
	return topPtr->data;
}
void convertToPostfix(char infix[], char postfix[]) {

	StackNodePtr topPtr = NULL;

	push(&topPtr, '(');
	int in = 0, post = 0;


	while (!isEmpty(topPtr)) {
		if (!infix[in]) break;

		if (infix[in] == ' ') {
			in++;
			continue;
		}

		if (infix[in] >= '0' && infix[in] <= '9') {
			postfix[post++] = infix[in++];
		}

		else if (infix[in] == '(') {
			push(&topPtr, '(');
			in++;
		}

		else if (isOperator(infix[in])) {
			while (!isEmpty(topPtr) && isOperator(stackTop(topPtr)) && precedence(stackTop(topPtr), infix[in]) >= 0) {
				postfix[post++] = pop(&topPtr);
			}
			push(&topPtr, infix[in++]);
		}
		else {
			while (!isEmpty(topPtr) && stackTop(topPtr) != '(') {
				postfix[post++] = pop(&topPtr);
			}
			if (!isEmpty(topPtr)) pop(&topPtr);
			in++;
		}
	}

	while (!isEmpty(topPtr) && stackTop(topPtr) != '(') {
		postfix[post++] = pop(&topPtr);
	}

	postfix[post] = '\0';
	printf("The post fix of the expression is: ");
	for (int i = 0; postfix[i]; ++i) {
		printf("%c ", postfix[i]);
	}
	printf("\n");
}

int main() {
	char infix[] = "(6+2)*5-8/4";
	char postfix[1000000];
	printf("The expression entered is(infix): %s\n", infix);
	convertToPostfix(infix, postfix);

	system("pause");
	return 0;
}