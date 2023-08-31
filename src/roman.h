#pragma once

#include <optional>
#include <string>
#include <string_view>

class RomanNumeral
{
public:
  RomanNumeral();
  RomanNumeral(int decimal);
  RomanNumeral(std::string_view numeral);

  std::string roman() const;
  int decimal() const;

private:
  int decimal_;
  mutable std::optional<std::string> roman_;
};
