#include "vector_utils.hpp"

#include <iostream>
#include <vector>

// build and run:
// g++ -I ../common ./day1.cpp -o ../build/day1 && ../build/day1

int main() {
  // string path = "./input_test.txt";
  std::string path = "./input.txt";

  std::vector<std::string> lines = utils::extractFileToLineVector(path);
  // append empty string to get last entry processed
  lines.push_back("");

  std::vector<int> sums;

  int current_sum{0};

  for (unsigned int i = 0; i < lines.size(); ++i) {
    std::string current_line = lines[i];
    if (current_line == "") {
      sums.push_back(current_sum);
      current_sum = 0;
    } else {
      current_sum += stoi(current_line);
    }
  }

  std::vector<int> three_largest_vals = utils::getMaxNValsFromVector(sums, 3);
  std::cout << "EXC 1A:\t" << three_largest_vals.at(0) << std::endl;
  std::cout << "EXC 1B:\t" << utils::sumOverVectorElements(three_largest_vals)
            << std::endl;
}
