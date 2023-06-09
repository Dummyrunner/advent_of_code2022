// #include "catch_include.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

// build and run
// make clean && make && ../build/day5

class Crate {
public:
  Crate(int ip) : val{ip} {}
  void setVal(int ip) { val = ip; }
  int getVal() { return val; };

private:
  int val{0};
};

using stringVector = std::vector<std::string>;
using crateStack = std::vector<std::stack<Crate>>;
double squareNumber(double ip) { return ip * ip; }

std::vector<stringVector> splitStringVectorAtEmptyLine(stringVector str_vec) {
  std::vector<stringVector> res;
  stringVector current_vec_to_fill;
  for (size_t i{0}; i < str_vec.size(); ++i) {
    auto current_string = str_vec[i];
    if (current_string == "") {
      res.push_back(current_vec_to_fill);
      current_vec_to_fill.clear();
    } else {
      current_vec_to_fill.push_back(current_string);
    }
  }
  res.push_back(current_vec_to_fill);
  return res;
}

void replaceCharsInString(char old_char, char new_char, std::string &str) {
  for (int i{0}; i < str.size(); ++i) {
    if (str[i] == old_char) {
      str[i] = new_char;
    }
  }
}

void removeCharFromString(char char_to_remove, std::string &str) {
  str.erase(std::remove(str.begin(), str.end(), char_to_remove), str.end());
}

void removeBracketsFromString(std::string &str) {
  removeCharFromString('[', str);
  removeCharFromString(']', str);
}

int maximalDigitInString(std::string &str) {
  // Ugly af. how to convert char to corresponding int val??
  int current_max{0};
  for (int i{0}; i < str.size(); ++i) {
    char current_char = str[i];
    if (std::isdigit(current_char)) {
      current_max = current_max < current_char ? current_char : current_max;
    }
  }
  current_max -= 48;
  return current_max;
}

int main() {
  std::string path = "./input_test.txt";
  //   std::string path = "./input.txt";

  int total_score_A{0};
  int total_score_B{0};

  std::cout << "YO" << std::endl;

  stringVector test_strvec{"Hund", "Katze",      "Maus",
                           "",     "schaf",      "krokodil",
                           "",     "schokolade", "gummibaer"};

  auto vec_of_vecs = splitStringVectorAtEmptyLine(test_strvec);
  std::string test_string{"Hallo ciao"};
  replaceCharsInString(' ', '#', test_string);
  removeCharFromString('#', test_string);

  std::cout << test_string << " after replacement: " << test_string
            << std::endl;

  for (auto strvec : vec_of_vecs) {
    utils::printAllVectorEntries(strvec);
    std::cout << "-----------\n";
  }

  std::cout << "------------------------------------------------------------\n";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);
  auto parted_input_lines = splitStringVectorAtEmptyLine(lines);
  stringVector init_state_input{parted_input_lines[0]};
  stringVector moves_input{parted_input_lines[1]};
  // std::cout << "-----------\n";
  std::cout << " init state:\n", utils::printAllVectorEntries(init_state_input);
  std::cout << "-----------\n";
  utils::printAllVectorEntries(moves_input);
  std::cout << "-----------\n";

  std::cout << "endline of init state: " << init_state_input.back()
            << std::endl;
  const int num_of_stacks = maximalDigitInString(init_state_input.back());
  std::cout << "num of stacks: " << num_of_stacks << std::endl;

  crateStack Stacks;

  std::string init_state_line{"[Z] [M] [P]"};
  std::string init_state_line2{"    [D]    "};
  replaceCharsInString(' ', '#', init_state_line);
  replaceCharsInString(' ', '#', init_state_line2);
  std::cout << init_state_line << std::endl;
  std::cout << init_state_line2 << std::endl;
  //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
