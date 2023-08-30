#include "generate.h"

#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace roman {
namespace {

struct NumeralSet
{
  std::string next;
  std::string half;
  std::string curr;
  std::string subtract;
};

// clang-format off
std::map<int, NumeralSet> g_numeral_sets{
    {7, {"", "", "M̅"}},
    {6, {"M̅", "D̅", "C̅"}},
    {5, {"C̅", "L̅", "X̅"}},
    {4, {"X̅", "V̅", "M", "I̅"}},
    {3, {"M", "D", "C"}},
    {2, {"C", "L", "X"}},
    {1, {"X", "V", "I"}},
};
// clang-format on

std::string repeat(const std::string& str, int n)
{
  std::ostringstream os;
  for (int i = 0; i < n; ++i)
  {
    os << str;
  }
  return os.str();
}

void collect_digits(std::vector<int>& digits, int num)
{
  if (num > 9)
  {
    collect_digits(digits, num / 10);
  }
  digits.push_back(num % 10);
}

std::vector<int> digits(int decimal)
{
  std::vector<int> result;
  collect_digits(result, decimal);
  return result;
}

std::string digit_to_roman(size_t position, int digit)
{
  auto numeral = g_numeral_sets.at(position);

  // https://en.wikipedia.org/wiki/Roman_numerals//Standard_form

  switch (digit)
  {
  case 1: // 1 => C
  case 2: // 2 => CC
  case 3: // 3 => CCC
  {
    return repeat(numeral.curr, digit);
  }

  case 4: // 4 => CD
  {
    auto curr = (!numeral.subtract.empty()) ? numeral.subtract : numeral.curr;
    return std::format("{}{}", curr, numeral.half);
  }

  case 5: // 5 => V
  {
    return std::format("{}", numeral.half);
  }

  case 6: // 6 => DC
  case 7: // 7 => DCC
  case 8: // 8 => DCCC
  {
    auto count = digit - 5;
    auto buffer = numeral.half + repeat(numeral.curr, count);
    return buffer;
  }

  case 9: // 9 => CM
  {
    auto curr = (!numeral.subtract.empty()) ? numeral.subtract : numeral.curr;
    return std::format("{}{}", curr, numeral.next);
  }

  case 0: // 0 => ''
  {
    return "";
  }

  default:
    throw std::runtime_error(std::format("invalid digit value: {}", digit));
  }
}

} // namespace

std::string generate(int decimal)
{
  if (decimal == 0)
  {
    return "N";
  }

  // TODO: Range check negative numbers?

  const auto decimal_digits = digits(decimal);
  if (decimal_digits.size() > g_numeral_sets.size())
  {
    throw std::out_of_range(
        std::format("Can only manage decimal numbers up to {} digits", g_numeral_sets.size()));
  }

  std::stringstream output;
  for (size_t i = 0; i < decimal_digits.size(); ++i)
  {
    const auto digit = decimal_digits[i];
    // Position from the right. (Base 1)
    const auto position = decimal_digits.size() - i;
    const auto numeral = digit_to_roman(position, digit);
    output << numeral;
  }
  return output.str();
}

} // namespace roman
