#include "cv_parser.h"

#include <stdbool.h>
#include <string.h>

/// @brief Convert a numeric character to its integer value.
#define NUMERIC_CHAR_TO_VALUE(c) ((c) - '0')

/// @brief Return true if the given character is a digit or the start of a digit spelled out.
/// @param c The character to check.
/// @return True if the given character is a digit or the start of a digit spelled out.
static bool cv_is_digit(const char *c) {
    // clang-format off
    return ('0' <= *c && *c <= '9')
    || (strncmp(c, "one", 3ULL) == 0)
    || (strncmp(c, "two", 3ULL) == 0)
    || (strncmp(c, "three", 5ULL) == 0)
    || (strncmp(c, "four", 4ULL) == 0)
    || (strncmp(c, "five", 4ULL) == 0)
    || (strncmp(c, "six", 3ULL) == 0)
    || (strncmp(c, "seven", 5ULL) == 0)
    || (strncmp(c, "eight", 5ULL) == 0)
    || (strncmp(c, "nine", 4ULL) == 0);
    // clang-format on
}

/// @brief Return the value of the given digit or digit spelled out.
/// @param c The digit or digit spelled out.
/// @return The value of the given digit or digit spelled out.
static int cv_digit_to_value(const char *c) {
    if ('0' <= *c && *c <= '9') return NUMERIC_CHAR_TO_VALUE(*c);

    if (strncmp(c, "one", 3ULL) == 0) return 1;

    if (strncmp(c, "two", 3ULL) == 0) return 2;

    if (strncmp(c, "three", 5ULL) == 0) return 3;

    if (strncmp(c, "four", 4ULL) == 0) return 4;

    if (strncmp(c, "five", 4ULL) == 0) return 5;

    if (strncmp(c, "six", 3ULL) == 0) return 6;

    if (strncmp(c, "seven", 5ULL) == 0) return 7;

    if (strncmp(c, "eight", 5ULL) == 0) return 8;

    if (strncmp(c, "nine", 4ULL) == 0) return 9;

    return 0;
}

int cv_parse(const char *calibration_str, size_t len) {
    const char *first_digit = NULL;
    const char *last_digit  = NULL;

    for (const char *c = calibration_str; c < calibration_str + len; c++) {
        if (cv_is_digit(c)) {
            first_digit = c;
            break;
        }
    }

    for (const char *c = calibration_str + len; c >= calibration_str; c--) {
        if (cv_is_digit(c)) {
            last_digit = c;
            break;
        }
    }

    if (!first_digit || !last_digit) return 0;

    int value = cv_digit_to_value(first_digit) * 10;
    value += cv_digit_to_value(last_digit);

    return value;
}