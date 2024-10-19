#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ARRAY_SIZE 20

bool ParseIntIsPosible(char* str) {
	int i = 0;
	if (str[0] == '-') {
		i++;
	}
	for (; str[i] != '\0'; ++i) {
		if (str[i] < 48 || str[i] > 57) {
			return false;
		}
	}
	return true;
}

int ParseInt(char* str) {
	int result = 0.0;
	int sign = 1;
	if (*str == '-') {
		sign = -1;
		str++;
	}
	while (*str) {
		result = result * 10.0 + (*str - '0');
		str++;
	}
	return result;
}

void Fill(int* arr, int size, int a, int b) {
	for (int i = 0; i != size; ++i) {
		arr[i] = rand() % (b - a + 1) + a;
	}
}

void SwapMaxMin(int* ar, int size) {
	int indexMax = 0;
	int indexMin = 0;
	for (int i = 0; i != size; ++i) {
		if (ar[i] < ar[indexMin]) {
			indexMin = i;
		}
		if (ar[i] > ar[indexMax]) {
			indexMax = i;
		}
	}
	int tmp = ar[indexMax];
	ar[indexMax] = ar[indexMin];
	ar[indexMin] = tmp;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Wrong arguments\n");
		return 1;
	}
	int a, b;
	if (ParseIntIsPosible(argv[1])) {
		a = ParseInt(argv[1]);
	}
	else {
		printf("Wrong first argument\n");
		return 2;
	}
	if (ParseIntIsPosible(argv[2])) {
		b = ParseInt(argv[2]);
	}
	else {
		printf("Wrong second argument\n");
		return 3;
	}
	if (a > b) {
		printf("Wrong arguments\n");
		return 4;
	}
	int array[ARRAY_SIZE];
	Fill(array, ARRAY_SIZE, a, b);
	printf("Before swap:\n");
	for (int i = 0; i != ARRAY_SIZE; ++i) {
		printf("%d ", array[i]);
	}
	SwapMaxMin(array, ARRAY_SIZE);
	printf("\nAfter swap:\n");
	for (int i = 0; i != ARRAY_SIZE; ++i) {
		printf("%d ", array[i]);
	}
}