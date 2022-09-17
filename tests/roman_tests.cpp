#include "roman.h"
#include "roman_literals.h"

#include <cassert>
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <vector>

namespace {

class TestSuite;
TestSuite* g_test_suite_;

class TestSuite {
 public:
  TestSuite(const std::string& name) : name_(name) {
    assert(g_test_suite_ == nullptr);
    g_test_suite_ = this;

    std::cout << name << "\n\n";
  }
  ~TestSuite() {
    std::cout << "\n\n";
    for (const auto& failure : failures_)
    {
      std::cout << failure << "\n";
    }

    g_test_suite_ = nullptr;
  }

  const std::string& name() const {
    return name_;
  }

  void record(const std::string& failure) {
    failures_.push_back(failure);
  }

  bool failed() const {
    return !failures_.empty();
  }

  const std::vector<std::string>& failures() const {
    return failures_;
  }

 private:
  std::string name_;
  std::vector<std::string> failures_;
};

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
    g_test_suite_->record(message);
  }
}

} // namespace

int main(int argc, char* argv[])
{
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
