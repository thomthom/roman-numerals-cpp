#pragma once

#include <string_view>
#include <vector>

#include "token.h"

namespace roman {

std::vector<Token> lex(std::string_view input);

} // namespace roman
