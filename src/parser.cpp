#include "parser.h"

#include <string>

namespace roman {

int parse(const std::vector<Token>& tokens) {
  int sum = 0;
  int previous_value = 0;
  int buffer_sum = 0;
  for (const auto token : tokens) {
    // Read the characters in chunks. Each chunk consists of the same token.
    // Add up the sum for the chunk and compare against the previous token
    // chunk whether to add or subtract to the total sum.
    auto value = token.value;
    if (value == previous_value) {
      buffer_sum += value;
    } else {
      if (value > previous_value && previous_value > 0) {
        sum -= buffer_sum;
      } else {
        sum += buffer_sum;
      }
      buffer_sum = value;
    }
    previous_value = value;
  }
  return sum + buffer_sum;
}

} // namespace roman
