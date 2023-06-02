#include "../day5.cpp"

TEST_CASE("squares is computed", "[squaredNumber]") {
  REQUIRE(squaredNumber(0.) == 0);
  REQUIRE(squaredNumber(0.5) == 0.25);
  REQUIRE(squaredNumber(5.) == 25);
}
