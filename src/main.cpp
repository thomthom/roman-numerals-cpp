#include "roman.h"

#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "Decimal to Roman Numerals\n";

  if (argc <= 1)
  {
    std::cout << "Usage: roman DECIMAL...\n";
    std::cout << "Examples:\n";
    std::cout << "  roman 1983\n";
    std::cout << "  roman 1983 123\n";
    return 0;
  }

  for (int i = 1; i < argc; ++i)
  {
    const auto input = argv[i];
    const auto decimal = std::stoi(input);
    const auto numeral = RomanNumeral(decimal);
    std::cout << std::setw(2) << i << ". " << std::setw(6) << decimal << " => " << numeral.roman()
              << "\n";
  }
  return 0;
}
