#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "colorizecheck.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32

#include <io.h>

#define isatty(fd) (_isatty(fd) != 0)
#define STDOUT_FILENO _fileno(stdout)

#else // _WIN32

#include <unistd.h>

#endif

static bool should_colorize;
static bool cached = false;

static bool _get_should_colorize() {
    // algorithm from
    // https://github.com/termcolor/termcolor/blob/8e1621bc6907e45f9e15b52c9c7e2b04e6193084/src/termcolor/termcolor.py

    char *ANSI_COLORS_DISABLED = getenv("ANSI_COLORS_DISABLED");
    if (ANSI_COLORS_DISABLED && *ANSI_COLORS_DISABLED) {
        return false;
    }
    char *NO_COLOR = getenv("NO_COLOR");
    if (NO_COLOR && *NO_COLOR) {
        return false;
    }
    char *FORCE_COLOR = getenv("FORCE_COLOR");
    if (FORCE_COLOR && *FORCE_COLOR) {
        return true;
    }
    char *TERM = getenv("TERM");
    if (TERM && strcmp(TERM, "dumb") == 0) {
        return false;
    }

    return isatty(STDOUT_FILENO);
}

bool consolestyles_should_colorize() {
    if (!cached) {
        should_colorize = _get_should_colorize();
        cached = true;
    }
    return should_colorize;
}

void consolestyles_override_should_colorize(bool enabled) {
    should_colorize = enabled;
    cached = true;
}

void consolestyles_reset_should_colorize() {
    cached = false;
}
