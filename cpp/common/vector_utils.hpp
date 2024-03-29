#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace utils {

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

std::vector<std::string> extractFileToLineVector(std::string const &file_path) {
  std::fstream file;
  std::string read;
  std::vector<std::string> lines;
  try {
    file.open(file_path);
    if (!file) {
      throw std::runtime_error("file failed to open");
    }
    while (getline(file, read)) {
      lines.push_back(read);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return lines;
}

template <typename TypeT> void dropDuplicates(std::vector<TypeT> &vec) {
  std::sort(vec.begin(), vec.end());
  auto last = std::unique(vec.begin(), vec.end());
  vec.erase(last, vec.end());
}

std::string vecOfCharsToString(std::vector<char> charvec) {
  return std::string(charvec.begin(), charvec.end());
}
} // namespace utils
