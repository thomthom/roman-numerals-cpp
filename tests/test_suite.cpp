#include "test_suite.h"

#include <cassert>
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <vector>

namespace roman {

TestSuite* g_test_suite_;
TestSuite* CurrentTestSuite()
{
  return g_test_suite_;
};

TestSuite::TestSuite(const std::string& name) : name_(name)
{
  assert(g_test_suite_ == nullptr);
  g_test_suite_ = this;

  std::cout << COLOR_CYAN << name << COLOR_RESET << "\n\n";
}
TestSuite::~TestSuite()
{
  std::cout << "\n\n";
  for (const auto& failure : failures_)
  {
    std::cout << failure << "\n";
  }

  g_test_suite_ = nullptr;
}

const std::string& TestSuite::name() const
{
  return name_;
}

void TestSuite::record(const std::string& failure)
{
  failures_.push_back(failure);
}

bool TestSuite::failed() const
{
  return !failures_.empty();
}

const std::vector<std::string>& TestSuite::failures() const
{
  return failures_;
}

} // namespace roman
