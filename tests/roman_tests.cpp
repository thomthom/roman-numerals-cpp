#include "roman.h"

#include <format>
#include <iostream>
#include <string>
#include <vector>

namespace {

std::vector<std::string> g_failures;

template<typename T, typename U>
void ASSERT_EQ(T expected, U actual)
{
  if (expected == actual)
  {
    std::cout << ".";
  }
  else
  {
    std::cout << "F";

    std::string message =
        std::format("Expected {} to equal {}.", actual, expected);
    g_failures.push_back(message);
  }
}

} // namespace

int main(int argc, char* argv[])
{
  std::cout << "Roman Numeral Tests\n";

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

  std::cout << "\n";
  for (const auto& failure : g_failures)
  {
    std::cout << failure << "\n";
  }
}
