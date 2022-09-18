#include "test_suite.h"

#include "roman.h"
#include "roman_literals.h"

int main(int argc, char* argv[])
{
  using namespace roman;

  TestSuite test_suite("Roman Numeral Tests");
  {
    const RomanNumeral numeral(1983);
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1983, numeral.decimal());
  }

  {
    const RomanNumeral numeral("MCMLXXXIII");
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1983, numeral.decimal());
  }

  {
    const auto numeral = 1983_roman;
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1983, numeral.decimal());
  }

  {
    const auto numeral = "MCMLXXXIII"_roman;
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    ASSERT_EQ(1983, numeral.decimal());
  }

  return test_suite.failed() ? 1 : 0;
}
