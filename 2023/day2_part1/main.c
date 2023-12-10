#include <stdio.h>
#include <string.h>

#include "cube_game.h"

#define MAX_LINE_LEN 256

#define NUM_RED_CUBES   12
#define NUM_GREEN_CUBES 13
#define NUM_BLUE_CUBES  14

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

    cg_cube_count cube_count = {
        .red_cubes = NUM_RED_CUBES, .green_cubes = NUM_GREEN_CUBES, .blue_cubes = NUM_BLUE_CUBES};

    char current_line[MAX_LINE_LEN] = {0};
    size_t total                    = 0;
    while (fgets(current_line, MAX_LINE_LEN, input_file)) {
        cg_cube_game cg = cg_from_string(current_line, strnlen(current_line, MAX_LINE_LEN));

        if (cg_is_possible(cg, cube_count)) total += cg.number;
    }

    printf("%zu\n", total);

    fclose(input_file);

    return 0;
}
