#include "cube_game.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256

#define ROUND_DELIMITERS ";"
#define SET_DELIMITERS   ","

/// @brief Return the count of each cube parsed from a line of the form "x red, y blue, z green",
/// where any of the colors may be missing and order does not matter.
/// @param line The line to parse.
/// @param line_len The length of the line.
/// @return The count of each cube represented by the line.
static cg_cube_count cg_round_count_from_string(const char *line, size_t line_len) {
    char line_copy[MAX_LINE_LEN] = {0};
    strncpy(line_copy, line, line_len);

    cg_cube_count round_count = {0};

    char *strtok_ctx = NULL;
    char *token      = strtok_r((char *)line_copy, SET_DELIMITERS, &strtok_ctx);

    while (token != NULL) {
        size_t cube_count = strtoull(token, &token, 10);
        // (1)

        token++;  // Skip the space after the number
        if (strncmp(token, "red", 3ULL) == 0)
            round_count.red_cubes += cube_count;
        else if (strncmp(token, "green", 5ULL) == 0)
            round_count.green_cubes += cube_count;
        else if (strncmp(token, "blue", 4ULL) == 0)
            round_count.blue_cubes += cube_count;

        token = strtok_r(NULL, SET_DELIMITERS, &strtok_ctx);
    }

    return round_count;
}

cg_cube_game cg_from_string(const char *line, size_t line_len) {
    cg_cube_game cg = {0};

    // TODO(Caleb): This looks ugly...
    char line_copy_data[MAX_LINE_LEN] = {0};
    char *line_copy                   = line_copy_data;
    strncpy(line_copy_data, line, line_len);

    cg.number = strtoull(line_copy + 5, &line_copy, 10);  // Start after "Game "
    // Note(Caleb): Handle errors from strtol here. But those would never happen, right? (1)

    char *strtok_ctx = NULL;
    char *round_str =
        strtok_r(line_copy + 2, ROUND_DELIMITERS, &strtok_ctx);  // Start after "Game xxx: "

    while (round_str != NULL) {
        cg_cube_count round =
            cg_round_count_from_string(round_str, strnlen(round_str, MAX_LINE_LEN));

        assert(cg.num_rounds < CG_MAX_ROUND_COUNT);
        cg.rounds[cg.num_rounds++] = round;

        round_str = strtok_r(NULL, ROUND_DELIMITERS, &strtok_ctx);
    }

    return cg;
}

bool cg_is_possible(const cg_cube_game game, const cg_cube_count cube_count) {
    for (size_t i = 0; i < game.num_rounds; i++) {
        cg_cube_count current_round = game.rounds[i];

        bool game_is_possible = (current_round.red_cubes <= cube_count.red_cubes)
                             && (current_round.green_cubes <= cube_count.green_cubes)
                             && (current_round.blue_cubes <= cube_count.blue_cubes);

        if (!game_is_possible) return false;
    }

    return true;
}
