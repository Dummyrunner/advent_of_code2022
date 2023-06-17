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

// class SolverDay5 {
// public:
//   std::string solveA() {}

// private:
//   CrateStackParser parser;
//   std::unique_ptr<CrateStackCollection> cscA = nullptr;
// };

int main() {
  // std::string path = "./input_test.txt";
  std::string path = "./input.txt";

  std::string final_tops_A{};
  std::string final_tops_B{};

  CrateStackParser parser = CrateStackParser(path);

  // Parse init state input
  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();
  utils::printAllVectorEntries(preprocessedInitStateStringVec);

  CrateStackCollection cscA =
      CrateStackCollection(preprocessedInitStateStringVec);
  auto moveDirectivesVectorA{parser.getMoveDirectivesVector()};

  for (int i = 0; i < moveDirectivesVectorA.size(); ++i) {
    cscA.moveOneByOne(moveDirectivesVectorA[i]);
  }

  // CrateStackCollection cscB =
  //     CrateStackCollection(preprocessedInitStateStringVec);
  // auto moveDirectivesVectorB{parser.getMoveDirectivesVector()};

  // for (int i = 0; i < moveDirectivesVectorB.size(); ++i) {
  //   cscB.moveOneByOne(moveDirectivesVectorB[i]);
  // }

  std::cout << std::endl;
  final_tops_A = cscA.topCratesToString();
  // final_tops_B = cscB.topCratesToString();
  cscA.printTopCrates();

  std::cout << "EXC 4A:\t" << final_tops_A << std::endl;
  std::cout << "EXC 4B:\t" << final_tops_B << std::endl;
}
