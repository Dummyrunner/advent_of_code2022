// #include "catch_include.hpp"
#include "crate_stack_collection.hpp"
#include "crate_stack_parser.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

// build and run
// make clean && make && ../build/day5

int main() {
  // std::string path = "./input_test.txt";
  std::string path = "./input.txt";

  int total_score_A{0};
  int total_score_B{0};

  stringVector test_strvec{"Hund", "Katze",      "Maus",
                           "",     "schaf",      "krokodil",

                           "",     "schokolade", "gummibaer"};
  CrateStackParser parser = CrateStackParser(path);

  // Parse init state input
  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();
  utils::printAllVectorEntries(preprocessedInitStateStringVec);

  CrateStackCollection x = CrateStackCollection(preprocessedInitStateStringVec);
  auto moveDirectivesVector{parser.getMoveDirectivesVector()};
  for (int i = 0; i < moveDirectivesVector.size(); ++i) {
    x.moveOneByOne(moveDirectivesVector[i]);
  }
  std::cout << "----------------------------------" << std::endl;
  x.printTopCrates();
  std::cout << std::endl;
  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
