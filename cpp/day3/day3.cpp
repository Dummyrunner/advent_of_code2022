#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day3/day3.cpp -o ./build/day3 && ./build/day3

bool containsChar(const std::string &s, const char c) {
  size_t str_len = s.size();
  for (uint i{0}; i < str_len; ++i) {
    if (s[i] == c) {
      return true;
    }
  }
  return false;
}

std::pair<std::string, std::string> splitStringInHalf(std::string s) {
  std::string str1;
  std::string str2;
  size_t str_len = s.size();
  if (str_len % 2 == 1) {
    throw std::runtime_error("tried to split string with odd number of chars");
  }
  size_t half_len = str_len / 2;
  str1 = s.substr(0, half_len);
  str2 = s.substr(half_len, half_len);
  std::pair<std::string, std::string> res;
  res.first = str1;
  res.second = str2;
  return res;
}

std::vector<char> commonChars(const std::string &str1,
                              const std::string &str2) {
  std::vector<char> res;
  for (auto c : str1) {
    if (containsChar(str2, c)) {
      res.push_back(c);
    }
  }
  return res;
}
// template <typename TypeT> void dropDuplicates(const std::vector<TypeT> &vec);

int valueFromChar(const char &c) {
  // a -> 1, z->26
  // A -> 27, Z->52
  int ascii{int(c)};
  if (ascii < 65 || ascii > 122) {
    throw std::runtime_error("given charactor is no alphabetical letter");
  }
  if (ascii < 97 && ascii > 90) {
    throw std::runtime_error("given charactor is no alphabetical letter");
  }
  bool c_is_lower_case{ascii > 96};
  return c_is_lower_case ? ascii - 96 : ascii - 38;
}

std::vector<char> commonCharsOfThreeStrings(const std::string &str1,
                                            const std::string &str2,
                                            const std::string &str3) {
  // auto std::vector<char> common_chars();
  auto common_chars = commonChars(str1, str2);
  std::string string_from_common_chars{utils::vecOfCharsToString(common_chars)};
  return commonChars(string_from_common_chars, str3);
}

int main() {
  // std::string path = "./day3/input_test.txt";
  std::string path = "./day3/input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  int total_score_A{0};
  std::vector<std::string> common_chars;
  for (std::string line : lines) {
    std::pair<std::string, std::string> split = splitStringInHalf(line);

    auto common_chars_for_this_line = commonChars(split.first, split.second);
    utils::dropDuplicates(common_chars_for_this_line);
    for (char c : common_chars_for_this_line) {
      total_score_A += valueFromChar(c);
    }
  }
  std::cout << "EXC 3A:\t" << total_score_A << std::endl;
  auto cs = commonCharsOfThreeStrings("abEc", "cDE", "Ecx");
  utils::printAllVectorEntries(cs);
  //   std::cout << "EXC 3B:\t" << total_score_B << std::endl;
}
