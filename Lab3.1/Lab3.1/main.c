#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <intrin.h>
#include <immintrin.h>
#include <stdlib.h>

int inc(int num) {
	if ((num & 1) == 0) {
		return num | 1;
	}
	else {
		return inc(num >> 1) << 1;
	}
}

int add(int a, int b) {
	while (b != 0) {
		int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

int subtract(int a, int b) {
	int neg_b = add(~b, 1);
	return add(a, neg_b);
}

char IntToChar(int x) { return (x < 10) ? add('0', x) : subtract(add('A', x), 10); }

bool IsValidBase(int base) {
	int valid_bases_mask = 0b111110;
	return (base >= 2 && base <= 32 && (valid_bases_mask & (1 << (_tzcnt_u32(base)))) &&
		(__popcnt(base) == 1));
}

void Reverse(char* string, int len) {
	for (int i = 0; i != len >> 1; i = inc(i)) {
		char tmp = string[i];
		string[i] = string[subtract(subtract(len, i), 1)];
		string[subtract(subtract(len, i), 1)] = tmp;
	}
}

int Translation(int number, int base, char* result) {
	if (!IsValidBase(base)) {
		return 1;
	}
	if (number == 0) {
		result[0] = '0';
		result[1] = '\0';
		return 0;
	}
	int result_index = 0;
	bool sign = (number < 0) ? 1 : 0;
	number = abs(number);
	while (number) {
		int mod = number & (subtract(base, 1));
		result[result_index] = IntToChar(mod);
		result_index = inc(result_index);
		number >>= _tzcnt_u32(base);
	}
	if (sign) {
		result[result_index] = '-';
		result_index = inc(result_index);
	}
	result[result_index] = '\0';
	Reverse(result, result_index);
}

int main() {
	int number = 24534;
	char res[33];
	printf("The number %d in the binary system: ", number);
	Translation(number, 2, res);
	printf("%s\n", res);

	printf("The number of %d in the quaternary system: ", number);
	Translation(number, 4, res);
	printf("%s\n", res);

	printf("The number %d in the octal system: ", number);
	Translation(number, 8, res);
	printf("%s\n", res);

	printf("The number %d in the hexadecimal system: ", number);
	Translation(number, 16, res);
	printf("%s\n", res);

	printf("The number %d in the thirty-two-dimensional system: ", number);
	Translation(number, 32, res);
	printf("%s\n", res);

	return 0;
}
