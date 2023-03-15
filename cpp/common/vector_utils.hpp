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
template <typename TypeT> void printAllVectorEntries(std::vector<TypeT> &vec);

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
} // namespace utils
