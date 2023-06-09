#include "interval.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// make clean && make && ../build/day4

std::vector<std::string> splitStringAtChar(const std::string &str,
                                           char separator) {
  std::vector<std::string> res;
  std::string read{};
  std::stringstream sstr{str};
  while (getline(sstr, read, separator)) {
    res.push_back(read);
  }
  return res;
}

std::pair<int, int> parseIntMinusIntToPair(const std::string &str) {
  std::pair<int, int> res;
  std::vector<std::string> nums_as_string_vec = splitStringAtChar(str, '-');
  res.first = stoi(nums_as_string_vec[0]);
  res.second = stoi(nums_as_string_vec[1]);
  return res;
}

int main() {
  // std::string path = "./input_test.txt";
  std::string path = "./input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  int total_score_A{0};
  int total_score_B{0};

  for (auto line : lines) {
    auto vec_of_substrings = splitStringAtChar(line, ',');
    std::vector<std::pair<int, int>> range_pairs;
    for (auto rangestring : vec_of_substrings) {
      range_pairs.push_back(parseIntMinusIntToPair(rangestring));
    }
    auto pair1 = range_pairs[0];
    auto pair2 = range_pairs[1];
    Interval<int> interval1 = Interval<int>(pair1.first, pair1.second);
    Interval<int> interval2 = Interval<int>(pair2.first, pair2.second);

    if (interval1.includes(interval2) || interval2.includes(interval1)) {
      ++total_score_A;
    }
    if (interval1.intersects(interval2)) {
      ++total_score_B;
    }
  }
  std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
