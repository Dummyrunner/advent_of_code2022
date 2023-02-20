#include "vector_utils.hpp"

int main() {
  // string path = "./day1/input_test.txt";
  std::string path = "./day1/input.txt";

  std::vector<std::string> lines = extractFileToLineVector(path);
  // append empty string to get last entry processed
  lines.push_back("");

  std::vector<int> sums;

  int current_sum{0};

  for (int i = 0; i < lines.size(); ++i) {
    std::string current_line = lines[i];
    if (current_line == "") {
      sums.push_back(current_sum);
      current_sum = 0;
    } else {
      current_sum += stoi(current_line);
    }
  }

  std::vector<int> three_largest_vals = getMaxNValsFromVector(sums, 3);
  std::cout << "EXC 1A:\t" << three_largest_vals.at(0) << std::endl;
  std::cout << "EXC 1B:\t" << sumOverVectorElements(three_largest_vals)
            << std::endl;
}
