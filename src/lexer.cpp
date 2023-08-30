#include "lexer.h"

#include <map>
#include <stdexcept>
#include <string_view>

namespace roman {
namespace {

// clang-format off
// A map of the Roman numerals and their decimal values.
const std::map<std::string, Token> ROMAN_TOKENS = {
  { "M̅", Token("M̅", 1'000'000) },
  { "D̅", Token("D̅", 500'000) },
  { "C̅", Token("C̅", 100'000) },
  { "L̅", Token("L̅", 50'000) },
  { "X̅", Token("X̅", 10'000) },
  { "V̅", Token("V̅", 5'000) },
  { "I̅", Token("I̅", 1'000) },
  { "M", Token("M", 1'000) },
  { "D", Token("D", 500) },
  { "C", Token("C", 100) },
  { "L", Token("L", 50) },
  { "X", Token("X", 10) },
  { "V", Token("V", 5) },
  { "I", Token("I", 1) },
  { "N", Token("N", 0) },
};
// clang-format on

// Prefix `_` before a numeral to multiply it by `1000`.
// This is an ASCII alternative to the unicode notation.
const std::string MEGA_MODIFIER_PREFIX = "_";

// A Unicode postfix modifier multiplying the preceding
// numeral by `1000`.
// TODO: This ends up as a single byte std::string, even with utf-8 flag.
// const std::string MEGA_MODIFIER_POSTFIX = "\u0305";
// 	0xcc85 / 0xcc 0x85 (2 bytes)
const std::string MEGA_MODIFIER_POSTFIX = "\xcc\x85";

// List of numerals that can be modified by the thousand modifiers.
const std::string MODIFIABLE_NUMERALS = "MDCLXVI";

class LexError : public std::domain_error
{
public:
  LexError(const char* message) : std::domain_error(message){};
};

} // namespace

std::vector<Token> lex(const std::string& input)
{
  if (input.empty())
    return {};

  std::vector<Token> tokens;
  bool mega = false;
  std::string_view input_view = input;
  for (size_t i = 0; i < input.size(); ++i)
  {
    const auto chr = input_view.substr(i, 1);

    // Account for ASCII modifier to the numerals.
    if (mega && MODIFIABLE_NUMERALS.find(chr) == std::string::npos)
    {
      throw LexError("unexpected char after MEGA_MODIFIER_PREFIX: #{c}"); // TODO: Format
    }

    if (chr == MEGA_MODIFIER_PREFIX)
    {
      mega = true;
      continue;
    }

    // Account for possible Combining Overline diacritics.
    // https://en.wikipedia.org/wiki/Combining_character
    if (input_view.substr(i, MEGA_MODIFIER_POSTFIX.size()) == MEGA_MODIFIER_POSTFIX)
    {
      ++i; // Because MEGA_MODIFIER_POSTFIX is byte size 2.
      continue;
    }

    std::string buffer(chr);

    // Look ahead to see if there's an overline, indicating multiplication by 1000.
    const auto peek = input_view.substr(i + 1, MEGA_MODIFIER_POSTFIX.size());
    if (peek == MEGA_MODIFIER_POSTFIX)
    {
      buffer = input_view.substr(i, 1 + MEGA_MODIFIER_POSTFIX.size());
      // Can't combine ASCII notation and Unicode chars.
      if (mega)
        throw LexError("unexpected char after MEGA_MODIFIER_PREFIX: #{chr}"); // TODO: Format
    }

    // Convert the ASCII notation to Unicode notation.
    if (mega)
      buffer = std::string(chr) + MEGA_MODIFIER_POSTFIX;

    const auto it = ROMAN_TOKENS.find(buffer);
    if (it == ROMAN_TOKENS.end())
      throw LexError("invalid numeral: #{buffer}"); // TODO: Format

    // Reset the MEGA state now that we have the full char.
    mega = false;

    const auto token = it->second;
    tokens.push_back(token);
  }
  return tokens;
}

} // namespace roman
