#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day4/day4.cpp -o ./build/day4 && ./build/day4

int main() {
  // std::string path = "./day3/input_test.txt";
  std::string path = "./day3/input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  //   std::cout << "EXC 3A:\t" << total_score_A << std::endl;
  //   std::cout << "EXC 3B:\t" << total_score_B << std::endl;
}
