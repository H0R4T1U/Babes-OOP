#pragma once

/*
Checks if a given score is valid.
Params: score - the score to validate.
Returns: 1 if the score is valid (within the range 0 to 100), otherwise 0.
*/
int isValidScore(int score);

/*
Checks if a given name is valid.
Params: name - the name to validate.
Returns: 1 if the name is valid (non-empty and contains only alphabetic
characters), otherwise 0.
*/
int isValidName(const char *name);
