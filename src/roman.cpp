#include "roman.h"

namespace {

int parse(const std::string& roman)
{
  return 0; // TODO:
}

std::string generate(int decimal)
{
  return ""; // TODO:
}

} // namespace

RomanNumeral::RomanNumeral() : decimal_(0) {}
RomanNumeral::RomanNumeral(int decimal) : decimal_(decimal) {}
RomanNumeral::RomanNumeral(const std::string& numeral)
    : decimal_(parse(numeral)), roman_(numeral)
{}

std::string RomanNumeral::roman() const
{
  if (!roman_.has_value())
  {
    roman_ = generate(decimal_);
  }
  return roman_.value();
}

int RomanNumeral::decimal() const
{
  return decimal_;
}
