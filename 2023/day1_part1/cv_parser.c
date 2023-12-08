#include "cv_parser.h"

#include <stdbool.h>

#define NUMERIC_CHAR_TO_VALUE(c) ((c) - '0')

int cv_parse(const char *calibration_str, size_t len) {
    char first_digit = 0;
    char last_digit  = 0;

    // Find the first digit in the string
    for (const char *c = calibration_str; c < calibration_str + len; c++) {
        if ('0' <= *c && *c <= '9') {
            first_digit = *c;
            break;
        }
    }

    // Find the last digit in the string
    for (const char *c = calibration_str + len; c >= calibration_str; c--) {
        if ('0' <= *c && *c <= '9') {
            last_digit = *c;
            break;
        }
    }

    if (!first_digit || !last_digit) return 0;

    int value = 0;
    value += NUMERIC_CHAR_TO_VALUE(first_digit) * 10;
    value += NUMERIC_CHAR_TO_VALUE(last_digit);

    return value;
}