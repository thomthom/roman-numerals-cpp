#pragma once

#include "roman.h"

RomanNumeral operator"" _roman(unsigned long long value);
RomanNumeral operator"" _roman(const char* value, size_t size);
