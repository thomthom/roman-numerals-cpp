#include "test_suite.h"

#include "roman.h"
#include "roman_literals.h"

namespace {

void ASSERT_ROUNDTRIP(const std::string& roman, int decimal)
{
  using namespace roman;
  ASSERT_EQ(RomanNumeral(roman).decimal(), decimal);
  ASSERT_EQ(RomanNumeral(decimal).roman(), roman);
}

} // namespace

int main(int argc, char* argv[])
{
  using namespace roman;
  using namespace std::string_literals;

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

  {
    ASSERT_ROUNDTRIP("I̅V̅DVI", 4'506);
    ASSERT_EQ("MV̅DVI"_roman.decimal(), 4'506); // Alternative
    ASSERT_ROUNDTRIP("L̅X̅MMMCCCXXXIX", 63'339);
    ASSERT_ROUNDTRIP("C̅C̅X̅C̅I̅X̅DLV", 299'555);
    ASSERT_EQ("C̅C̅X̅C̅MX̅DLV"_roman.decimal(), 299'555); // Alternative
    ASSERT_ROUNDTRIP("M̅M̅D̅C̅L̅X̅V̅II", 2'665'002);
  }

  {
    ASSERT_EQ("_I_VDVI"_roman.decimal(), 4'506);
    ASSERT_EQ("M_VDVI"_roman.decimal(), 4'506); // Alternative
    ASSERT_EQ("_L_XMMMCCCXXXIX"_roman.decimal(), 63'339);
    ASSERT_EQ("_C_C_X_C_I_XDLV"_roman.decimal(), 299'555);
    ASSERT_EQ("_C_C_X_CM_XDLV"_roman.decimal(), 299'555); // Alternative
    ASSERT_EQ("_M_M_D_C_L_X_VII"_roman.decimal(), 2'665'002);
  }

  {
    ASSERT_ROUNDTRIP("N"s, 0);
  }

  {
    // Upper range.

    //                   9 IX (10 - 1)
    //                90 XC
    //             900 CM
    //          9000 I̅X̅ (10'000 - 1'000)
    //       90000 X̅C̅ (1'000'00 - 100'00)
    //    900000 (1'000'000 - 100'000)
    // 900000 (10'000'000 - 1'000'000) <- Can't represent ten million.
    // 9  9  9  9  9  9  9
    // M̅  C̅M̅ X̅C̅ I̅X̅ CM XC IX
    const RomanNumeral numeral(9'999'999);
    ASSERT_EQ("MCMLXXXIII", numeral.roman());
    // ASSERT_EQ(1983, numeral.decimal());

    // TODO: Is max 4'999'999? (No representation for five million...)

    ASSERT_ROUNDTRIP("M̅C̅M̅X̅C̅I̅X̅CMXCIX", 9'999'999);
  }

  {
    // Beyond range.
    const RomanNumeral numeral(10'000'000);
    try
    {
      const auto roman = numeral.roman();
    }
    catch (const std::out_of_range& exception)
    {
      ASSERT_EQ("Can only manage decimal numbers up to 7 digits"s, exception.what());
    }
  }

  return test_suite.failed() ? 1 : 0;
}
