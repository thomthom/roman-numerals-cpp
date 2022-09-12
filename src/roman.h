#pragma once

#include <optional>
#include <string>

class RomanNumeral
{
public:
  RomanNumeral();
  RomanNumeral(int decimal);
  RomanNumeral(const std::string& numeral);

  std::string roman() const;
  int decimal() const;

private:
  int decimal_;
  mutable std::optional<std::string> roman_;
};
