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
  std::string path = "./input_test.txt";
  //   std::string path = "./input.txt";

  int total_score_A{0};
  int total_score_B{0};

  std::cout << "YO" << std::endl;

  stringVector test_strvec{"Hund", "Katze",      "Maus",
                           "",     "schaf",      "krokodil",

                           "",     "schokolade", "gummibaer"};
  CrateStackParser parser = CrateStackParser(path);

  // Parse init state input
  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();
  utils::printAllVectorEntries(preprocessedInitStateStringVec);

  // Parse move input
  std::string teststr{"move 1 from 2 to 1"};
  auto movedirective = parser.moveDirectiveFromInputLine(teststr);
  std::cout << "amount: " << movedirective.amount << std::endl;
  std::cout << "target: " << movedirective.target << std::endl;
  std::cout << "origin: " << movedirective.origin << std::endl;

  CrateStackCollection x = CrateStackCollection(preprocessedInitStateStringVec);

  std::cout << "num of stacks: " << x.numOfStacks() << std::endl;
  x.moveTopFromStackToStack(0, 2, 2);
  std::cout << "top val of stack 0 " << x.peekTopVal(0) << std::endl;
  std::cout << "top val of stack 1 " << x.peekTopVal(1) << std::endl;
  std::cout << "top val of stack 2 " << x.peekTopVal(2) << std::endl;
  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
