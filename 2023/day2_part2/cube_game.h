#include <stdbool.h>
#include <stddef.h>

#define CG_MAX_ROUND_COUNT 8

/// @brief A count of the number of cubes of each color for a given round.
typedef struct {
    size_t red_cubes;
    size_t green_cubes;
    size_t blue_cubes;
} cg_cube_count;

/// @brief A cube game.
typedef struct {
    /// @brief The number of the cube game.
    size_t number;

    /// @brief The number of rounds in the cube game.
    cg_cube_count rounds[CG_MAX_ROUND_COUNT];

    /// @brief The number of rounds in the cube game.
    size_t num_rounds;
} cg_cube_game;

/// @brief Return a cube game resulting from the parsing of a line of the form "number: x c, y c,
/// ...; ..." (where x and y are positive integers and c is a color).
/// @param line The line to parse.
/// @param line_len The length of the line.
/// @return The cube game represented by the line.
cg_cube_game cg_from_string(const char *line, size_t line_len);

/// @brief Return true if the given cube game is possible given the number of cubes of each color,
/// false otherwise.
/// @param game The cube game to check.
/// @param cube_count The number of cubes of each color.
/// @return True if the given cube game is possible given the number of cubes of each color, false
/// otherwise.
bool cg_is_possible(const cg_cube_game game, const cg_cube_count cube_count);

/// @brief Return a cube count of the least amount of each cube required to make the cube game
/// possible.
/// @param cg The cube game to create a minimum cube count for.
/// @return A cube count of the least amount of each cube required to make the cube game possible.
cg_cube_count cg_minimum_cube_count(const cg_cube_game cg);

/// @brief Return the power of a count of cubes.
/// @param cc The cube count to calculate the power of.
/// @return The power of a count of cubes.
size_t cg_calculate_power(const cg_cube_count cc);
