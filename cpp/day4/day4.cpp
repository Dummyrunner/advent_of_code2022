#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day4/day4.cpp -o ./build/day4 && ./build/day4

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

template <typename TypeT> class Interval {
public:
  Interval(TypeT lower, TypeT upper) { setBounds(lower, upper); }
  void setBounds(TypeT lower, TypeT upper) {
    if (upper < lower) {
      throw std::runtime_error("Upper bound is smaller than lower bound!");
    }
    m_upper_bound = upper;
    m_lower_bound = lower;
  }

  bool includes(Interval &other) {
    return (this.m_upper_bound >= other.m_upper_bound &&
            this.m_lower_bound <= other.m_lower_bound);
  }

  // TODO bool intersects(Interval &other) {return false;}

private:
  TypeT m_upper_bound;
  TypeT m_lower_bound;
};

int main() {
  // std::string path = "./day4/input_test.txt";
  std::string path = "./day4/input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  std::string test_string = "1-2,3-4,5-6";
  auto res_vec = splitStringAtChar(test_string, ',');
  std::string one = res_vec.back();
  utils::printAllVectorEntries(res_vec);
  auto eumel = parseIntMinusIntToPair(one);

  std::cout << eumel.first << std::endl;
  std::cout << eumel.second << std::endl;

  //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
