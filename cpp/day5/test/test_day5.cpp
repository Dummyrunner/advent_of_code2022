#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"

TEST_CASE("squares is computed", "[squaredNumber]") {
  REQUIRE(squaredNumber(0.) == 0);
  REQUIRE(squaredNumber(0.5) == 0.25);
  REQUIRE(squaredNumber(5.) == 25);
}
