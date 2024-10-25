#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ComputePolynomialDerivative(double* derivativeCoeffs, int degree, double* originalCoeffs) {
	for (int i = 1; i <= degree; i++) {
		double currentCoeff = originalCoeffs[i];
		derivativeCoeffs[i - 1] = currentCoeff * i;
	}
	return 0;
}

int EvaluatePolynomial(int degree, double xValue, double* coefficients, double* result) {
	double evaluationResult = 0.0;
	for (int i = degree; i > 0; i--) {
		evaluationResult += coefficients[i];
		if (fabsl(evaluationResult) > DBL_MAX / fabsl(xValue)) {
			return 4;
		}
		evaluationResult *= xValue;
	}
	evaluationResult += coefficients[0];
	*result = evaluationResult;
	return 0;
}

int ComputeTaylorSeries(double epsilon, double expansionPoint, double* taylorCoeffs, int degree, ...) {
	double* originalCoeffs = (double*)calloc(degree + 1, sizeof(double));
	if (originalCoeffs == NULL) {
		return 5;
	}
	double* derivativeCoeffs = (double*)calloc(degree + 1, sizeof(double));
	if (derivativeCoeffs == NULL) {
		free(originalCoeffs);
		return 5;
	}

	va_list args;
	va_start(args, degree);
	for (int i = 0; i <= degree; i++) {
		originalCoeffs[i] = va_arg(args, double);
	}
	va_end(args);

	int status = EvaluatePolynomial(degree, expansionPoint, originalCoeffs, taylorCoeffs);
	if (status != 0) {
		free(originalCoeffs);
		free(derivativeCoeffs);
		return status;
	}

	double factorial = 1;
	for (int i = 1; i <= degree; i++) {
		factorial *= i;
		status = ComputePolynomialDerivative(derivativeCoeffs, degree, originalCoeffs);
		if (status != 0) {
			free(originalCoeffs);
			free(derivativeCoeffs);
			return status;
		}
		derivativeCoeffs[degree - i + 1] = 0.0;
		double derivativeValue;
		status = EvaluatePolynomial(degree, expansionPoint, derivativeCoeffs, &derivativeValue);
		taylorCoeffs[i] = derivativeValue / factorial;
		if (status != 0) {
			free(originalCoeffs);
			free(derivativeCoeffs);
			return status;
		}
		memcpy(originalCoeffs, derivativeCoeffs, sizeof(double) * degree);
	}
	free(originalCoeffs);
	free(derivativeCoeffs);
	return 0;
}

int PrintPolynomial(double* coefficients, int degree, double expansionPoint) {
	printf("g(x) = ");
	// ���� ��� ������ ������� ����� ��������
	for (int i = 0; i <= degree; i++) {
		if (i > 0 && coefficients[i] >= 0) {
			printf(" + ");
		}
		else if (i > 0) {
			printf(" - ");
			coefficients[i] = -coefficients[i];  // ��������� � ������������� ��� ������
		}

		// ������ ���������� �����
		if (i == 0) {
			printf("%.2f", coefficients[i]);
		}
		else {
			// ������ ������ �������� � ����������� �� ����� ����������
			if (expansionPoint > 0) {
				printf("%.2f * (x - %.2f)^%d", coefficients[i], expansionPoint, i);
			}
			else if (expansionPoint == 0) {
				printf("%.2f * (x)^%d", coefficients[i], i);
			}
			else {
				printf("%.2f * (x + %.2f)^%d", coefficients[i], fabs(expansionPoint), i);
			}
		}
	}
	printf("\n");
	return 0;
}

int main() {
	double coefficients1[5] = { 0.0, 0.0, 5.0 };
	double taylorCoeffs1[5];
	ComputeTaylorSeries(1e-6, -2.5, taylorCoeffs1, 2, 0.0, 0.0, 5.0);
	PrintPolynomial(taylorCoeffs1, 2, -2.5);
	double res = 0;
	EvaluatePolynomial(2, 1, coefficients1, &res);
	printf("%lf\n", res);
	res = 0;
	EvaluatePolynomial(2, -1.5, taylorCoeffs1, &res);
	printf("%lf\n", res);

	EvaluatePolynomial(2, 2, coefficients1, &res);
	printf("%lf\n", res);
	res = 0;
	EvaluatePolynomial(2, -0.5, taylorCoeffs1, &res);
	printf("%lf\n", res);


	double coefficients2[5] = { 5.0, 1.0, 2.0, 3.0 };
	double taylorCoeffs2[5];
	ComputeTaylorSeries(1e-6, 0.0, taylorCoeffs2, 3, 5.0, 1.0, 2.0, 3.0);
	PrintPolynomial(taylorCoeffs2, 3, 0.0);

	double coefficients3[5];
	double taylorCoeffs3[5];
	ComputeTaylorSeries(1e-6, 1.0, taylorCoeffs3, 4, -7.0, 0.0, 4.0, 0.0, -1.0);
	PrintPolynomial(taylorCoeffs3, 4, 1.0);

	double coefficients4[5];
	double taylorCoeffs4[5];
	ComputeTaylorSeries(1e-6, 3.0, taylorCoeffs4, 1, -2.0, 1.0);
	PrintPolynomial(taylorCoeffs4, 1, 3.0);

	return 0;
}