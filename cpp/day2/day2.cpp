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

int main() {
  std::string path = "./day2/input_test.txt";
  // std::string path = "./day2/input.txt";
  std::vector<std::string> lines = extractFileToLineVector(path);
  printAllVectorEntries(lines);

  for (int i = 0; i < 3; ++i) {
    auto x = splitCharPairSeparatedBy(lines[i], ' ');
    std::cout << x.first << std::endl;
    std::cout << x.second << std::endl;
  }
}
