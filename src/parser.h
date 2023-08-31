#pragma once

#include <span>
#include <vector>

#include "token.h"

namespace roman {

int parse(std::span<const Token> tokens);

} // namespace roman
