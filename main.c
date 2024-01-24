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

double numbers[SIZE] = { 0 };

int numbers_index = 0;

void print_all_numbers(int decimals)
{
	char buffer[30] = { 0 };
	printf("[ ");
	for (int i = 0; i < numbers_index; i++) {
		sprintf(buffer, "%%.%df ", decimals);
		printf(buffer, numbers[i]);
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
	double *a = &numbers[numbers_index - 1];
	double *b = &numbers[numbers_index];

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
		if (*a == 0) {
			printf("ARE YOU INSANE?!\n");
			numbers_index++;
			return;
		}
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
	char parsing_number = 0;
	// TODO registers?
	char clean_registers = 0;
	Operation current_op = O_NIL;
	char decimal_part = 0;
	int decimals = 0;
	double decimal_modifier = .1;
	double current_number = 0;

	if (argn > 1) {
		if (strcmp(argv[1], "-d") == 0) {
			decimals = atoi(argv[2]);
		} else {
			printf("-d for decimals\n");
			return 1;
		}
	}

	printf("Refer to README for how to use\n");
	printf("Clean numbers with =\n");

	for (;;) {
		c = getchar();

		if (c == EOF)
			break;

		if (c == '\n' || c == ' ') {
			if (parsing_number) {
				if (current_op == O_SUB) {
					current_number *= -1;
					current_op = O_NIL;
				}

				numbers[numbers_index++] = current_number;
				// b = buffer;

				parsing_number = 0;
				decimal_part = 0;
				current_number = 0;
				decimal_modifier = .1;
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

			print_all_numbers(decimals);
			continue;
		}

		if (isin(c, "+-*/")) {
			current_op = switch_op_char(c);
			continue;
		}

		if (c == '.') {
			decimal_part = 1;
		}

		if (c == 'r') {
			if (numbers_index < 2)
				continue;
			double aux = numbers[numbers_index-1];
			numbers[numbers_index-1] = numbers[numbers_index-2];
			numbers[numbers_index-2] = aux;
			continue;
		}

		if (c >= '0' && c <= '9') {
			if (decimal_part) {
				current_number += (c-'0') * decimal_modifier;
				decimal_modifier *= .1;
			} else {
				current_number =
				    (current_number * 10) + (c - '0');
			}
			parsing_number = 1;
		}

		if (c == '=') {
			clean_registers = 1;
		}
	}
}
