// #include "catch_include.hpp"
#include "crate_stack_collection.hpp"
#include "crate_stack_parser.hpp"
#include "vector_utils.hpp"
#include <iostream>
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

  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();

  CrateStackCollection cscA =
      CrateStackCollection(preprocessedInitStateStringVec);
  auto moveDirectivesVector{parser.getMoveDirectivesVector()};

  for (std::vector<MoveDirective>::size_type i = 0;
       i < moveDirectivesVector.size(); ++i) {
    cscA.moveOneByOne(moveDirectivesVector[i]);
  }

  CrateStackCollection cscB =
      CrateStackCollection(preprocessedInitStateStringVec);
  for (std::vector<MoveDirective>::size_type i = 0;
       i < moveDirectivesVector.size(); ++i) {
    cscB.moveWholeSubstack(moveDirectivesVector[i]);
  }

  final_tops_A = cscA.topCratesToString();
  final_tops_B = cscB.topCratesToString();

  std::cout << "EXC 4A:\t" << final_tops_A << std::endl;
  std::cout << "EXC 4B:\t" << final_tops_B << std::endl;
}
