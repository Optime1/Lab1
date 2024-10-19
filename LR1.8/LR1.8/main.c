#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int GetCharValue(char ch) {
	if (ch >= '0' && ch <= '9') {
		return ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A' + 10;
	}
	return -1;
}

long long translate(char* buf, int buf_index, int sys) {
	long long result = 0;
	long long pred = 0;
	for (int i = 0; i < buf_index; i++) {
		pred = result;
		result += GetCharValue(buf[i]) * (long long)pow(sys, buf_index - i - 1);
		if (pred > result) {
			return -1;
		}
	}
	return result;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Wrong arguments\n");
		return 1;
	}
	FILE* inputFile;
	FILE* outputFile;
	if (strcmp(argv[1], argv[2]) == 0) {
		printf("The input file is the same as the output file.\n");
		return 1;
	}
	if ((inputFile = fopen(argv[1], "w")) == NULL) {
		printf("Error opening input file.\n");
		return 1;
	}
	if ((outputFile = fopen(argv[2], "r")) == NULL) {
		printf("Error opening output file.\n");
		fclose(inputFile);
		return 2;
	}

	int sys = 0;
	int el;
	bool wordStarted = false;
	int bufIndex = 0;

	int bufferCapacity = 10;
	char* buffer = malloc(bufferCapacity * sizeof(char));
	if (buffer == NULL) {
		printf("Error allocating memory.\n");
		fclose(inputFile);
		fclose(outputFile);
		return 3;
	}

	while ((el = fgetc(inputFile)) != EOF) {
		if (!(el == ' ' || el == '\t' || el == '\n' || el == '\r')) {
			if (!wordStarted) {
				wordStarted = true;
				bufIndex = 0;
			}

			if (el >= 'a' && el <= 'z') {
				el -= 32;
			}

			if (bufIndex >= bufferCapacity) {
				bufferCapacity *= 2;
				char* tmp = realloc(buffer, bufferCapacity * sizeof(char));
				if (tmp == NULL) {
					free(buffer);
					fclose(inputFile);
					fclose(outputFile);
					return 4;
				}
				buffer = tmp;
			}

			int value = GetCharValue(el);
			if (value == 0 && bufIndex == 0) {
				continue;
			}
			if (value == -1) {
				printf("Invalid character in input\n");
				fclose(inputFile);
				fclose(outputFile);
				free(buffer);
				return 6;
			}
			if (value + 1 > sys) {
				sys = value + 1;
			}
			buffer[bufIndex] = el;
			++bufIndex;
		}
		else if (wordStarted) {
			if (bufIndex == 0) {
				buffer[0] = '0';
				++bufIndex;
			}
			if (bufIndex + 1 >= bufferCapacity) {
				bufferCapacity *= 2;
				char* tmp = realloc(buffer, bufferCapacity * sizeof(char));
				if (tmp == NULL) {
					free(buffer);
					fclose(inputFile);
					fclose(outputFile);
					return 4;
				}
				buffer = tmp;
			}
			buffer[bufIndex] = '\0';
			if (sys < 2) {
				sys = 2;
			}
			long long translatedValue = translate(buffer, bufIndex, sys);
			if (translatedValue == -1) {
				fprintf(outputFile, "%s %d Overflow\n", buffer, sys);
			}
			else {
				fprintf(outputFile, "%s %d %lld\n", buffer, sys, translatedValue);
			}
			wordStarted = false;
			sys = 0;
		}
	}

	if (wordStarted) {
		buffer[bufIndex] = '\0';
		long long translated_value = translate(buffer, bufIndex, sys);
		if (translated_value == -1) {
			fprintf(outputFile, "%s %d Overflow\n", buffer, sys);
		}
		else {
			fprintf(outputFile, "%s %d %lld\n", buffer, sys, translated_value);
		}
	}
	free(buffer);
	fclose(inputFile);
	fclose(outputFile);
	printf("$$$$$");
	return 0;
}