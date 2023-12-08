#include <stdio.h>
#include <string.h>

#include "cv_parser.h"

#define MAX_LINE_LEN 256

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("error: failed to open %s\n", argv[1]);
        return 1;
    }

    char current_line[MAX_LINE_LEN];
    int total = 0;
    while (fgets(current_line, MAX_LINE_LEN, input_file)) {
        int cv = cv_parse(current_line, strnlen(current_line, MAX_LINE_LEN));
        // printf("%d\n", cv);
        total += cv;
    }
    printf("%d\n", total);

    fclose(input_file);

    return 0;
}