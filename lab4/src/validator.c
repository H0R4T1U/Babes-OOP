#include "validator.h"

#include <ctype.h>
#include <string.h>

int isValidScore(int score) {
    return score >= 0 && score <= 100;
}

int isValidName(const char *name) {
    for (size_t i = 0, n = strlen(name); i < n; ++i) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }

    return 1;
}
