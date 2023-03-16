#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace utils {

template <typename TypeT>
std::vector<TypeT> getMaxNValsFromVector(std::vector<TypeT> vec,
                                         const int N = 1);

template <typename TypeT> TypeT sumOverVectorElements(std::vector<TypeT> &vec);
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
} // namespace utils
