#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
    char ch;

    if (!in || !out) {
        perror("Unable to open file");
        return;
    }

    while ((ch = fgetc(in)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
}

void count_letters(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
    char line[256];

    if (!in || !out) {
        perror("Unable to open file");
        return;
    }

    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i])) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
    }

    fclose(in);
    fclose(out);
}

void count_non_alpha_digits_spaces(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
    char line[256];

    if (!in || !out) {
        perror("Unable to open file");
        return;
    }

    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isalpha(line[i]) && !isdigit(line[i]) && !isspace(line[i])) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
    }

    fclose(in);
    fclose(out);
}

void replace_with_ascii_hex(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
    char ch;

    if (!in || !out) {
        perror("Unable to open file");
        return;
    }

    while ((ch = fgetc(in)) != EOF) {
        if (!isdigit(ch)) {
            fprintf(out, "%02X", (unsigned char)ch);
        }
        else {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Need flag and path\n");
        return 1;
    }

    char* flag = argv[1];
    char* input_file = argv[2];
    char output_file[256];

    if (argc == 4) {
        strcpy_s(output_file, sizeof(output_file), argv[3]);
    }
    else {
        snprintf(output_file, sizeof(output_file), "out_%s", input_file);
    }

    if (strcmp(flag, "-d") == 0) {
        remove_digits(input_file, output_file);
    }
    else if (strcmp(flag, "-i") == 0) {
        count_letters(input_file, output_file);
    }
    else if (strcmp(flag, "-s") == 0) {
        count_non_alpha_digits_spaces(input_file, output_file);
    }
    else if (strcmp(flag, "-a") == 0) {
        replace_with_ascii_hex(input_file, output_file);
    }
    else {
        printf("Unknown flag\n");
        return 1;
    }

    return 0;
}