// #include "catch_include.hpp"
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

using stringVector = std::vector<std::string>;

// struct MoveDirective {
// public:
//   MoveDirective(int aim, int origin, int amount)
//       : aim{aim}, origin{origin}, amount{amount} {}

//   int aim{};
//   int origin{};
//   int amount{};
// };

class Crate {
public:
  Crate(int ip) : val{ip} {}
  void setVal(int ip) { val = ip; }
  int getVal() { return val; };

private:
  int val{0};
};

using crateStack = std::vector<std::stack<Crate>>;

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

  parser.prepareInitStateInput();
  auto x = parser.getPreprocessedInputStateVector();
  utils::printAllVectorEntries(x);
  std::string teststr{"move 1 from 2 to 1"};
  // std::cout << "before drop: #" << teststr << std::endl;
  // parser.dropFirstNCharsOfString(teststr, 5);
  // std::cout << "after drop: #" << teststr << std::endl;
  // auto first_num_in_line{teststr[0]};
  // std::cout << "first char of string: " << first_num_in_line << std::endl;
  // std::cout << "test calculation (1): " <<
  // parser.charAsInt(first_num_in_line)
  //           << std::endl;
  auto movedirective = parser.moveDirectiveFromInputLine(teststr);
  std::cout << movedirective.amount << std::endl;
  std::cout << movedirective.aim << std::endl;
  std::cout << movedirective.origin << std::endl;

  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
