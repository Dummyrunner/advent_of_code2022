#include "vector_utils.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <typename TypeT>
std::vector<TypeT> getMaxNValsFromVector(std::vector<TypeT> vec,
                                         const int N = 1) {
  std::vector<TypeT> max_entries;
  for (int imax_entry = 0; imax_entry < N; ++imax_entry) {
    TypeT max_val = std::numeric_limits<TypeT>::min();
    size_t max_index{0};
    for (int i = 0; i < vec.size(); ++i) {
      if (vec[i] > max_val) {
        max_val = vec[i];
        max_index = i;
      }
    }
    max_entries.push_back(max_val);
    vec.erase(vec.begin() + max_index);
  }
  return max_entries;
}

template <typename TypeT> TypeT sumOverVectorElements(std::vector<TypeT> &vec) {
  TypeT sum{0};
  for (auto el : vec) {
    sum += el;
  }
  return sum;
}

template <typename TypeT> void printAllVectorEntries(std::vector<TypeT> &vec) {
  for (auto el : vec) {
    std::cout << el << std::endl;
  }
}
