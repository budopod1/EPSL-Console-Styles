#ifndef COLORIZECHECK_H
#define COLORIZECHECK_H

#include <stdbool.h>

#define EPSL_COMMON_PREFIX "consolestyles_"
#define EPSL_IMPLEMENTATION_LOCATION "colorizecheck.c"

bool consolestyles_should_colorize();

void consolestyles_override_should_colorize(bool enabled);

void consolestyles_reset_should_colorize();

#endif
