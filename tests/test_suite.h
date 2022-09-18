#pragma once

#include <cassert>
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <vector>

namespace roman {

constexpr const char* COLOR_RED = "\x1B[31m";
constexpr const char* COLOR_GREEN = "\x1B[32m";
constexpr const char* COLOR_YELLOW = "\x1B[33m";
constexpr const char* COLOR_BLUE = "\x1B[34m";
constexpr const char* COLOR_MAGENTA = "\x1B[35m";
constexpr const char* COLOR_CYAN = "\x1B[36m";
constexpr const char* COLOR_RESET = "\033[0m";

class TestSuite;
TestSuite* CurrentTestSuite();

class TestSuite {
 public:
  TestSuite(const std::string& name) ;
  ~TestSuite();

  const std::string& name() const;

  void record(const std::string& failure);
  bool failed() const;
  const std::vector<std::string>& failures() const;

 private:
  std::string name_;
  std::vector<std::string> failures_;
};

template<typename T, typename U>
void ASSERT_EQ(
    T expected, U actual,
    const std::source_location location = std::source_location::current())
{
  if (expected == actual)
  {
    std::cout << COLOR_GREEN << "." << COLOR_RESET;
  }
  else
  {
    std::cout << COLOR_RED << "F" << COLOR_RESET;

    std::string source =
        std::format("function {} : {}:{}:{}", location.function_name(),
                    location.file_name(), location.line(), location.column());

    std::string message =
        std::format("Expected \x1B[33m{}\033[0m to equal \x1B[33m{}\033[0m in {}.", actual, expected, source);
    CurrentTestSuite()->record(message);
  }
}

} // namespace
