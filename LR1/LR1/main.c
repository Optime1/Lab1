#include "stdio.h"
#include "conio.h"
#include "math.h"

#define MINNUM '0'
#define NUMBEROFFUNCTIONS 6

void FromIntToHex(int number) {
	if (number == 0) {
		printf("0\n");
		return;
	}
	int hex_digits[8];
	int num_digits = 0;

	while (number > 0) {
		hex_digits[num_digits] = number % 16;
		number /= 16;
		num_digits++;
	}

	for (int i = num_digits - 1; i >= 0; --i) {
		if (hex_digits[i] < 10) {
			printf("%d", hex_digits[i]);
		}
		else {
			printf("%c", 'A' + (hex_digits[i] - 10));
		}
		if (i > 0) {
			printf(" ");
		}
	}
	printf("\n");
}


void DegreeTable(int number) {
	if (number < 0 || number > 10) {
		printf("Number must be from 1 to 10\n");
	}
	for (int base = 1; base <= 10; ++base) {
		printf("BASE %d:  ", base);
		long long result = 1;
		for (int exponent = 1; exponent <= number; ++exponent) {
			result *= base;
			printf("%d^%d = %lld  ", base, exponent, result);
		}
		printf("\n");
	}
}

void ArifSum(int number) {
	printf("%d\n", (1 + number) * (number) / 2);
	return;
}

static const long long int factTable[] = {
	1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
	479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,
	355687428096000, 6402373705728000, 121645100408832000,
	2432902008176640000
};


void Factorial(int number) {
	if (number < 0) {
		printf("Negative number\n");
		return;
	}
	if (number > 20) {
		printf("The answer is too long\n");
		return;
	}
	printf("%lld", factTable[number]);
}

void IsSimpleNumber(int number) {
	if (number == 2) {
		printf("%i IS simple number\n", number);
	}
	double sqrtNumber = sqrt(number) + 1;
	for(int i = 2; i < sqrtNumber; ++i)
	{
		if (number % i == 0) {
			printf("%i IS NOT simple number!\n", number );
			return;
		}
	}
	printf("%i IS simple number\n", number);
	return;
}

void MultipliersNumber(int number) {
	int i = 1;
	while (number * i <= 100) {
		printf("%i, ", number * i);
		++i;
	}
	if (i == 1) {
		printf("No such numbers");
	}
	printf("\n");
	return;
}

int StrToInt(char* str) {
	int answer = 0;
	int modifier = 1;
	int len = strlen(str);
	for (int i = len - 1; i >= 0; --i) {
		answer += (str[i] - MINNUM) * modifier;
		modifier *= 10;
	}
	return answer;
}

int FlagToInt(char flag) {
	char flagSymbols[NUMBEROFFUNCTIONS] = { 'h', 'p', 's', 'e', 'a', 'f' };
	for (int i = 0; i < NUMBEROFFUNCTIONS; i++) {
		if (flag == flagSymbols[i]) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char** argv){
	if (argc != 3) {
		if (argc == 2 && strcmp(argv[1], "-i") == 0) {
			printf("""\
-h *number* - natural number from 1 to 100 multiplies n\n\
-p *number* - is simple number\n\
-s *number* - to hex\n\
-e *number* - table of degrees\n\
-a *number* - summ of natural number from 1 to n\n\
-f *number* - factorial of number\n""");
			return;
		}
		printf("Incorrect number of arguments. Check -i\n");
		return;
	}
	char flag = argv[1][1];
	void (*functions[NUMBEROFFUNCTIONS])(int) = {
		MultipliersNumber, // h
		IsSimpleNumber,    // p
		FromIntToHex,      // s
		DegreeTable,       // e
		ArifSum,           // a
		Factorial          // f
	};
	int number = StrToInt(argv[2]);
	int numberOfFunction = FlagToInt(flag);
	if (numberOfFunction == -1) {
		printf("No such flag");
		return;
	}
	functions[numberOfFunction](number);
	return;
}
