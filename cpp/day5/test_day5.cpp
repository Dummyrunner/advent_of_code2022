#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "day5.cpp"

// g++ -I ../common test_day5.cpp -o ../build/test_day5

TEST_CASE("Split string Vector on empty line",
          "[splitStringVectorAtEmptyLine]") {
  using stringVector = std::vector<std::string>;
  stringVector test_input{"dog", "cat", "mouse", "", "apple", "grape"};
  std::vector<stringVector> desired_output{};
  stringVector desired_sublist1{"dog", "cat", "mouse"};
  stringVector desired_sublist2{"apple", "grape"};

  desired_output.push_back(desired_sublist1);
  desired_output.push_back(desired_sublist2);
  auto test_output{splitStringVectorAtEmptyLine(test_input)};

  REQUIRE(desired_output == test_output);
}
