#include "error.h"
#include "stdio.h"
#include "math.h"

int ParseArg(int argc, char** argv, double* eps) {
	if (argc != 2) {
		return ERR_INVALID_ARGS;
	}

	char* option = argv[1];
	double result = 0.0;
	double mult = 1;
	int flag_dec = 1;
	for (char* i = option; *i; ++i) {
		if (*i >= '0' && *i <= '9') {
			if (flag_dec) {
				result *= 10;
				result += *i - '0';
			}
			else {
				mult /= 10;
				result += (*i - '0') * mult;
			}
		}
		else if (*i == '.' && flag_dec == 1) {
			flag_dec = 0;
		}
		else if (*i == '.') {
			return ERR_INVALID_ARGS;
		}
	}
	*eps = result;
	return SUCCESS;
}

double fact(int n) {
	double res = 1;
	for (int i = 2; i <= n; ++i) {
		res *= i;
	}
	return res;
}

double MyPow(double num, int degree) {
	double result = num;
	for (int n = 1; n < degree; n++) {
		result *= num;
	}
	return result;
}

double func1(int n) {
	return (1 / fact(n));
}

double func2(int n) {
	return (MyPow(-1, n - 1)) / (2 * n - 1);
}

double func3(int n) {
	return (MyPow(-1, n - 1)) / (n);
}

double func4(int n) {
	return MyPow(2, MyPow(2, -n));
}

double func5(int n) {
	return ((1) / (MyPow(sqrt(n), 2)) - (1) / (n));
}

double SumOfRow(double eps, double (*func)(int), int start) {
	int n = start;
	double prev_sum = -INFINITY;
	double cur_sum = 0;

	while (fabs(cur_sum - prev_sum) >= eps) {
		prev_sum = cur_sum;
		cur_sum += func(n);
		++n;
		printf("%lf\n", cur_sum);
	}

	return cur_sum;
}

double ProductOfRow(double eps, double (*func)(int), int start) {
	int n = start;
	double prev_sum = -INFINITY;
	double cur_sum = 1;

	while (fabs(cur_sum - prev_sum) >= eps) {
		prev_sum = cur_sum;
		cur_sum *= func(n);
		++n;
	}

	return cur_sum;
}

double Equation(double eps, double (*func)(int)) {
	double max = 1000;
	double min = -998;
	double answer = 0;

	//while()
}

int main(int argc, char** argv) {
	int return_code = SUCCESS;

	double eps = 0.0;

	return_code = ParseArg(argc, argv, &eps);


	double answer = SumOfRow(eps, func1, 0);

	printf("%lf\n", log(1));

	
	return 0;
}