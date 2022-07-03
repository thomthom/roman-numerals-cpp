#include "roman.h"

#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <vector>

namespace {

std::vector<std::string> g_failures;

template<typename T, typename U>
void ASSERT_EQ(
    T expected, U actual,
    const std::source_location location = std::source_location::current())
{
  if (expected == actual)
  {
    std::cout << ".";
  }
  else
  {
    std::cout << "F";

    std::string source =
        std::format("function {} : {}:{}:{}", location.function_name(),
                    location.file_name(), location.line(), location.column());

    std::string message =
        std::format("Expected {} to equal {} in {}.", actual, expected, source);
    g_failures.push_back(message);
  }
}

} // namespace

int main(int argc, char* argv[])
{
  std::cout << "Roman Numeral Tests\n\n";

  {
    RomanNumeral numeral(1984);
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1984, numeral.decimal());
  }

  {
    RomanNumeral numeral("MCMLXXXIII");
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1984, numeral.decimal());
  }

  std::cout << "\n\n";
  for (const auto& failure : g_failures)
  {
    std::cout << failure << "\n";
  }
}
