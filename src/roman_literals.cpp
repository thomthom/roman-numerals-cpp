#include "roman_literals.h"

#include <cassert>
#include <limits>

RomanNumeral operator"" _roman(unsigned long long value)
{
  assert(value <= std::numeric_limits<int>::max());
  return { static_cast<int>(value) };
}

RomanNumeral operator"" _roman(const char* value, size_t size)
{
  return { std::string_view(value, size) };
}
