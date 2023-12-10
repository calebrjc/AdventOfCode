#include <stdio.h>
#include <string.h>

#include "cube_game.h"

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

    char current_line[MAX_LINE_LEN] = {0};
    size_t total                    = 0;
    while (fgets(current_line, MAX_LINE_LEN, input_file)) {
        cg_cube_game cg  = cg_from_string(current_line, strnlen(current_line, MAX_LINE_LEN));
        cg_cube_count cc = cg_minimum_cube_count(cg);
        total += cg_calculate_power(cc);
    }

    printf("%zu\n", total);

    fclose(input_file);

    return 0;
}
