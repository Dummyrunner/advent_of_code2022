#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

template <typename TypeT>
vector<TypeT> getMaxNValsFromVector(vector<TypeT> vec, const int N = 1) {
  vector<TypeT> max_entries;
  for (int imax_entry = 0; imax_entry < N; ++imax_entry) {
    TypeT max_val = numeric_limits<TypeT>::min();
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

template <typename TypeT> TypeT sumOverVectorElements(vector<TypeT> &vec) {
  TypeT sum{0};
  for (auto el : vec) {
    sum += el;
  }
  return sum;
}

template <typename TypeT> void printAllVectorEntries(vector<TypeT> &vec) {
  for (auto el : vec) {
    cout << el << endl;
  }
}

vector<string> extractFileToLineVector(string const &file_path) {
  fstream file;
  string read;
  vector<string> lines;
  try {
    file.open(file_path);
    if (!file) {
      throw runtime_error("file failed to open");
    }
    while (getline(file, read)) {
      lines.push_back(read);
    }
  } catch (exception &e) {
    cerr << e.what() << endl;
  }
  return lines;
}

int main() {
  // string path = "./day1/input_test.txt";
  string path = "./day1/input.txt";

  vector<string> lines = extractFileToLineVector(path);
  // append empty string to get last entry processed
  lines.push_back("");

  vector<int> sums;

  int current_sum{0};

  for (int i = 0; i < lines.size(); ++i) {
    string current_line = lines[i];
    if (current_line == "") {
      sums.push_back(current_sum);
      current_sum = 0;
    } else {
      current_sum += stoi(current_line);
    }
  }

  vector<int> three_largest_vals = getMaxNValsFromVector(sums, 3);
  cout << "EXC 1A:\t" << three_largest_vals.at(0) << endl;
  cout << "EXC 1B:\t" << sumOverVectorElements(three_largest_vals) << endl;
}
