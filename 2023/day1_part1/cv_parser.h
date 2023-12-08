#include <stddef.h>

/// @brief Return the calibration value from a string.
/// @param calibration_str The string to parse.
/// @param len The length of the string.
/// @return The calibration value.
int cv_parse(const char *calibration_str, size_t len);