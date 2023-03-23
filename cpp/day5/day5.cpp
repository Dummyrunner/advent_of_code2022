#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day4/day4.cpp -o ./build/day4 && ./build/day4

int main() {
  std::string path = "./day4/input_test.txt";
  //   std::string path = "./day4/input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);

  int total_score_A{0};
  int total_score_B{0};

  //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
