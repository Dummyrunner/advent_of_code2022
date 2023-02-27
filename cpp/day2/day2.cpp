#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <string>

// g++ -I ./common ./day2/day2.cpp -o ./build/day2

std::pair<char, char> splitCharPairSeparatedBy(std::string str,
                                               char separator_char) {
  std::string first_char_as_string;
  std::string second_char_as_string;
  std::pair<char, char> res_pair;
  std::stringstream sstr(str);
  getline(sstr, first_char_as_string, separator_char);
  getline(sstr, second_char_as_string, separator_char);
  res_pair.first = first_char_as_string[0];
  res_pair.second = second_char_as_string[0];
  return res_pair;
}

enum class RockPaperScissors { kRock = 0, kPaper, kScissors };

RockPaperScissors getMoveFromChar(const char &input_char) {
  try {
    if (input_char == 'A' || input_char == 'X') {
      return RockPaperScissors::kRock;
    } else if (input_char == 'B' || input_char == 'Y') {
      return RockPaperScissors::kPaper;
    } else if (input_char == 'C' || input_char == 'Z') {
      return RockPaperScissors::kScissors;
    } else {
      throw input_char;
    }
  } catch (char wrong_char) {
    std::cerr << "char is not valid: " << wrong_char;
  }
}

int main() {
  std::string path = "./day2/input_test.txt";
  // std::string path = "./day2/input.txt";
  std::vector<std::string> lines = extractFileToLineVector(path);
  printAllVectorEntries(lines);

  // for (int i = 0; i < 3; ++i) {
  auto x = splitCharPairSeparatedBy(lines[0], ' ');
  //   std::cout << x.first << std::endl;
  //   std::cout << x.second << std::endl;
  // }
  // std::cout << getMoveFromChar(x.first) << "\t" << getMoveFromChar(x.second);
}
