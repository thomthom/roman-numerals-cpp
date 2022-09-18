#pragma once

#include <string>
#include <vector>

#include "token.h"

namespace roman {

std::vector<Token> lex(const std::string& input);

} // namespace roman
