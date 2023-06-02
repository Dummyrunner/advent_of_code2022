// #include "catch_include.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// build and run:
// g++ -I ./common ./day5.cpp -o ./day5 && ./build/day5

using stringVector = std::vector<std::string>;

double squareNumber(double ip) { return ip * ip; }
// std::vector<stringVector> splitStringVectorAtEmptyLine(stringVector str_vec)
// {
//   std::vector<stringVector> res;
//   stringVector current_vec_to_fill;
//   for (size_t i{0}; i < str_vec.size(); ++i) {
//     auto current_string = str_vec[i];
//     if (current_string == "") {
//       res.push_back(current_vec_to_fill);
//       current_vec_to_fill.clear();
//     } else {
//       current_vec_to_fill.push_back();
//     }
//   }
//   // std::pair<stringVector, stringVector> res;
//   // res.first = vec1;
//   // res.second = vec2;
//   return res;
// }

int main(int argc, char *argv[]) {
  std::string path = "./input_test.txt";
  //   std::string path = "./input.txt";
  std::vector<std::string> lines = utils::extractFileToLineVector(path);
  const double num = 5;
  std::cout << "number " << num << " squared " << squareNumber(num)
            << std::endl;
  int total_score_A{0};
  int total_score_B{0};
  std::cout << "YO" << std::endl;
  //   std::cout << "EXC 4A:\t" << total_score_A << std::endl;
  //   std::cout << "EXC 4B:\t" << total_score_B << std::endl;
}
