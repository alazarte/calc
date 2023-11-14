#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100

typedef enum OPERATION {
	O_ADD,
	O_SUB,
	O_DIV,
	O_MUL,
	O_NIL,
} Operation;

int numbers[SIZE] = { 0 };
char buffer[SIZE] = { 0 };

int numbers_index = 0;

void print_all_numbers()
{
	printf("[ ");
	for (int i = 0; i < numbers_index; i++) {
		printf("%d ", numbers[i]);
	}
	printf("]\n");
}

char isin(char c, char *in)
{
	while (*in != '\0') {
		if (c == *in)
			return 1;
		in++;
	}
	return 0;
}

void perform_operation(Operation op)
{
	if (numbers_index <= 1) {
		printf("ERROR: not enough numbers to operate\n");
		return;
	}

	numbers_index--;
	int *a = &numbers[numbers_index - 1];
	int *b = &numbers[numbers_index];

	switch (op) {
	case O_ADD:
		*a = *b + *a;
		break;
	case O_SUB:
		*a = *b - *a;
		break;
	case O_MUL:
		*a = *b * *a;
		break;
	case O_DIV:
		*a = *b / *a;
		break;
	}

	*b = 0;
}

void print_debug_info()
{
	printf("numbers_index=%d\n", numbers_index);
	printf("first ten elements=");
	for (int i = 0; i < 10; i++) {
		printf("%d ", numbers[i]);
	}
	printf("\n");
}

Operation switch_op_char(char ch)
{
	switch (ch) {
	case '+':
		return O_ADD;
	case '-':
		return O_SUB;
	case '*':
		return O_MUL;
	case '/':
		return O_DIV;
	default:
		return O_NIL;
	}
}

int main(int argn, char **argv)
{
	char c;
	char *b = buffer;
	// to avoid parsing a number when performing an operation
	// if the line only contains a '+' for example, should
	// only perform a adding operation, but not try to parse a
	// number from the buffer, I don't like this, find some
	// other way
	char parsing_number = 0;
	// TODO registers?
	char clean_registers = 0;
	Operation current_op = O_NIL;

	printf("Refer to README for how to use\n");
	printf("Clean numbers with =\n");

	for (;;) {
		c = getchar();

		if (c == EOF)
			break;

		if (c == '\n' || c == ' ') {
			if (parsing_number) {
				// always update current buffer pointer
				*b = '\0';

				int n = atoi(buffer);
				if (current_op == O_SUB) {
					n *= -1;
					current_op = O_NIL;
				}

				numbers[numbers_index++] = n;
				b = buffer;

				parsing_number = !parsing_number;
			} else {
				if (current_op != O_NIL) {
					perform_operation(current_op);
					current_op = O_NIL;
				}
			}
		}

		if (c == '\n') {
			if (clean_registers) {
				numbers_index = 0;
				clean_registers = 0;
				current_op = O_NIL;
			}

			print_all_numbers();
			continue;
		}

		if (isin(c, "+-*/")) {
			current_op = switch_op_char(c);
			continue;
		}

		if (c >= '0' && c <= '9') {
			parsing_number = 1;
			*b++ = c;
		}

		if (c == '=') {
			clean_registers = 1;
		}
	}
}

// TODO implement decimals
