// #include "catch_include.hpp"
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

class Crate {
public:
  Crate(int ip) : val{ip} {}
  void setVal(int ip) { val = ip; }
  int getVal() { return val; };

private:
  int val{0};
};

class CrateStackParser {
public:
  CrateStackParser(std::string path, const std::string empty_crate_char = "_")
      : m_filepath_to_parse{path}, m_empty_crate_char{empty_crate_char} {}

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

  void replaceSubstring(std::string &str, std::string str_to_be_replaced,
                        std::string replacement_str) {
    str = std::regex_replace(str, std::regex(str_to_be_replaced),
                             replacement_str);
  }

  void prepareInitStateInput() {
    std::vector<std::string> all_lines =
        utils::extractFileToLineVector(m_filepath_to_parse);
    auto two_input_sections = splitStringVectorAtEmptyLine(all_lines);
    auto init_state_input_lines = two_input_sections[0];

    std::string enum_line = init_state_input_lines.back();
    // remove last line enumerating stacks
    init_state_input_lines.erase(init_state_input_lines.end() - 1);

    for (auto &line : init_state_input_lines) {
      replaceCharsInString(' ', '#', line);
      replaceSubstring(line, "###", "[" + m_empty_crate_char + "]");
      removeCharFromString('#', line);
      removeBracketsFromString(line);
    }
    m_preprocessed_input_state_vector = init_state_input_lines;
    // utils::printAllVectorEntries(m_preprocessed_input_state_vector);
  }

  stringVector getPreprocessedInputStateVector() {
    return m_preprocessed_input_state_vector;
  }

  std::string getEmptyCrateChar() { return m_empty_crate_char; }

private:
  std::string m_filepath_to_parse{};
  std::string m_empty_crate_char{};
  stringVector m_preprocessed_input_state_vector{};
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
  auto vec_of_vecs = parser.splitStringVectorAtEmptyLine(test_strvec);
  std::string test_string{"Hallo ciao"};
  parser.replaceCharsInString(' ', '#', test_string);
  parser.removeCharFromString('#', test_string);

  parser.prepareInitStateInput();
  auto x = parser.getPreprocessedInputStateVector();
  std::cout << "HUDDLDIHÖH\n";
  utils::printAllVectorEntries(x);

  std::cout << test_string << " after replacement: " << test_string
            << std::endl;

  for (auto strvec : vec_of_vecs) {
    utils::printAllVectorEntries(strvec);
    std::cout << "-----------\n";
  }

  std::cout << "------------------------------------------------------------\n";
  // std::vector<std::string> lines = utils::extractFileToLineVector(path);
  // auto parted_input_lines = parser.splitStringVectorAtEmptyLine(lines);
  // stringVector init_state_input{parted_input_lines[0]};
  // stringVector moves_input{parted_input_lines[1]};
  // // std::cout << "-----------\n";
  // std::cout << " init state:\n",
  // utils::printAllVectorEntries(init_state_input); std::cout <<
  // "-----------\n"; utils::printAllVectorEntries(moves_input); std::cout <<
  // "-----------\n";

  // std::cout << "endline of init state: " << init_state_input.back()
  //           << std::endl;
  // const int num_of_stacks =
  //     parser.maximalDigitInString(init_state_input.back());
  // std::cout << "num of stacks : " << num_of_stacks << std::endl;

  // crateStack Stacks;

  // std::string init_state_line{"[Z] [M] [P]"};
  // std::string init_state_line2{"    [D]    "};
  // parser.replaceCharsInString(' ', '#', init_state_line);
  // parser.replaceCharsInString(' ', '#', init_state_line2);

  // parser.replaceSubstring(init_state_line, "###", "[_]");
  // parser.replaceSubstring(init_state_line2, "###", "[_]");

  // parser.removeCharFromString('#', init_state_line);
  // parser.removeCharFromString('#', init_state_line2);

  // parser.removeBracketsFromString(init_state_line);
  // parser.removeBracketsFromString(init_state_line2);
  // std::cout << init_state_line << std::endl;
  // std::cout << init_state_line2 << std::endl;
  // //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  // //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
