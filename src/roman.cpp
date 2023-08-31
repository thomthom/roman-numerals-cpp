#include "roman.h"

#include "generate.h"
#include "lexer.h"
#include "parser.h"

namespace {

int parse(std::string_view numeral)
{
  const auto tokens = roman::lex(numeral);
  return roman::parse(tokens);
}

std::string generate(int decimal)
{
  return roman::generate(decimal);
}

} // namespace

RomanNumeral::RomanNumeral() : decimal_(0) {}
RomanNumeral::RomanNumeral(int decimal) : decimal_(decimal) {}
RomanNumeral::RomanNumeral(std::string_view numeral) : decimal_(parse(numeral)), roman_(numeral) {}

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
