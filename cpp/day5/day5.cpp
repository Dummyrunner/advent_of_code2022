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

  CrateStackParser parser = CrateStackParser(path);
  std::string teststr{"move 10 from 6 to 8"};
  std::string teststr2{"move 1 from 6 to 8"};

  auto extracted_ints_vec = parser.extractIntegersFromString(teststr);
  std::cout << "--------------------------------" << std::endl;
  utils::printAllVectorEntries(extracted_ints_vec);
  std::cout << "--------------------------------" << std::endl;

  auto extracted_ints_vec2 = parser.extractIntegersFromString(teststr2);
  std::cout << "--------------------------------" << std::endl;
  utils::printAllVectorEntries(extracted_ints_vec2);
  std::cout << "--------------------------------" << std::endl;

  // Parse init state input
  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();
  utils::printAllVectorEntries(preprocessedInitStateStringVec);

  CrateStackCollection x = CrateStackCollection(preprocessedInitStateStringVec);
  auto moveDirectivesVector{parser.getMoveDirectivesVector()};
  int idir{0};
  for (auto move_directive : moveDirectivesVector) {
    std::cout << idir << "  move directive: (" << move_directive.origin << ","
              << move_directive.target << "," << move_directive.amount
              << ")  \n";
    ++idir;
  }
  for (int i = 0; i < moveDirectivesVector.size(); ++i) {
    x.moveOneByOne(moveDirectivesVector[i]);
  }

  std::cout << "----------------------------------" << std::endl;
  x.printTopCrates();
  std::cout << std::endl;
  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
