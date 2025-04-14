#pragma once
#include <token.h>

// Squashes patches of same tokens together `[{+, 1}, {+, 1}, {+, 1}] -> {+, 3}`
TokenString squash_tokens(TokenString *ts_in);
