#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100

int numbers[SIZE] = { 0 };
char buffer[SIZE] = { 0 };

int is_negative = 1;
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

void perform_operation(char op)
{
	if (numbers_index <= 1) {
		printf("ERROR: not enough numbers to operate\n");
		return;
	}

	numbers_index--;
	int *a = &numbers[numbers_index - 1];
	int *b = &numbers[numbers_index];

	switch (op) {
	case '+':
		*a = *b + *a;
		break;
	case '-':
		*a = *b - *a;
		break;
	case '*':
		*a = *b * *a;
		break;
	case '/':
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

	printf("Clean numbers with =\n");

	for (;;) {
		c = getchar();

		if (c == EOF)
			break;

		if (b == buffer && c == '-') {
			is_negative = -1;
			continue;
		}

		if (isin(c, "+-*/")) {
			perform_operation(c);
			continue;
		}

		if (c == '\n' || c == ' ') {
			if (parsing_number) {
				// always update current buffer pointer
				*b = '\0';
				numbers[numbers_index++] = atoi(buffer) * is_negative;
				b = buffer;

				is_negative = 1;
				parsing_number = !parsing_number;
			}
		}

		if (c == '\n') {
			if (clean_registers) {
				numbers_index = 0;
				is_negative = 1;
				clean_registers = 0;
			}

			// TODO well, when performing operation '-', it thinks a
			// negative number is going to be specified, so is ignored
			if (is_negative == -1) {
				perform_operation('-');
				is_negative = 1;
			}

			// print_debug_info();
			print_all_numbers();
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
