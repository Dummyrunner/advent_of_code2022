#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day3.cpp -o ../build/day3 && ../build/day3

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
  auto common_chars = commonChars(str1, str2);
  std::string string_from_common_chars{utils::vecOfCharsToString(common_chars)};
  common_chars = commonChars(string_from_common_chars, str3);
  utils::dropDuplicates(common_chars);
  return common_chars;
}

int main() {
  // std::string path = "./input_test.txt";
  std::string path = "./input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  int total_score_A{0};
  int total_score_B{0};

  std::vector<std::string> common_chars;
  std::vector<std::string> current_string_triplet;
  for (size_t iline{0}; iline < lines.size(); ++iline) {
    auto line = lines[iline];

    // EXC A
    std::pair<std::string, std::string> split = splitStringInHalf(line);
    auto common_chars_for_this_line = commonChars(split.first, split.second);
    utils::dropDuplicates(common_chars_for_this_line);
    for (char c : common_chars_for_this_line) {
      total_score_A += valueFromChar(c);
    }

    // EXC B
    current_string_triplet.push_back(line);
    if (iline != 0 && (iline + 1) % 3 == 0) {
      auto triplet_common_char_vec = commonCharsOfThreeStrings(
          current_string_triplet[0], current_string_triplet[1],
          current_string_triplet[2]);
      total_score_B += valueFromChar(triplet_common_char_vec[0]);
      current_string_triplet.clear();
    }
  }

  std::cout << "EXC 3A:\t" << total_score_A << std::endl;
  std::cout << "EXC 3B:\t" << total_score_B << std::endl;
}
