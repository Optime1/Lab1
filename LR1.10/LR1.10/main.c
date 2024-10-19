#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert a number from decimal system to a string representation in base 'base'
void to_base(unsigned long long value, int base, char* result) {
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[65];  // Temporary buffer for number conversion
    int pos = 0;

    if (value == 0) {
        strcpy_s(result, sizeof(result), "0");
        return;
    }

    // Convert the number to the desired base
    while (value > 0) {
        buffer[pos++] = digits[value % base];
        value /= base;
    }

    buffer[pos] = '\0';

    // Reverse the string because the number is stored in reverse order
    for (int i = 0; i < pos; i++) {
        result[i] = buffer[pos - i - 1];
    }
    result[pos] = '\0';
}

int main() {
    int base;
    char input[100];
    long long max_number = 0;

    printf("Enter the base of the number system (2-36): ");
    scanf_s("%d", &base);
    getchar();

    if (base < 2 || base > 36) {
        printf("Error: Base should be in the range [2..36].\n");
        return 1;
    }

    printf("Enter numbers in base %d system. Enter 'Stop' to finish.\n", base);

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Stop") == 0) {
            break;
        }

        char* endptr;
        long long number = strtoll(input, &endptr, base);

        if (*endptr != '\0') {
            printf("Error: Invalid input string.\n");
            continue;
        }

        if (llabs(number) > llabs(max_number)) {
            max_number = number;
        }
    }

    if (max_number == 0 && strcmp(input, "Stop") != 0) {
        printf("No numbers were entered.\n");
        return 0;
    }
    printf("Maximum number by modulus: %lld\n", max_number);

    char result[65];

    to_base(llabs(max_number), 9, result);
    printf("In base 9: %s\n", result);

    to_base(llabs(max_number), 18, result);
    printf("In base 18: %s\n", result);

    to_base(llabs(max_number), 27, result);
    printf("In base 27: %s\n", result);

    to_base(llabs(max_number), 36, result);
    printf("In base 36: %s\n", result);

    return 0;
}
