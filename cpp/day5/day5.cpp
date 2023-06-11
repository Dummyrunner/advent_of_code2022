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

class MoveDirective {
  MoveDirective(int aim, int origin, int amount)
      : m_aim{aim}, m_origin{origin}, m_amount{amount} {}

  int m_aim{};
  int m_origin{};
  int m_amount{};

  int getAim() { return m_aim; }
  int getOrigin() { return m_origin; }
  int getAmount() { return m_amount; }
};

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

  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
