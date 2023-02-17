#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

template <typename TypeT> TypeT getMaxValFromVector(vector<TypeT> &vec) {
  TypeT max_val = numeric_limits<TypeT>::min();
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i] > max_val) {
      max_val = vec[i];
    }
  }
  return max_val;
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

vector<string> extractPathToLineVector(string const &file_path) {
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

  vector<string> lines = extractPathToLineVector(path);
  vector<int> sums;

  int current_sum{0};
  // TODO: Last entry skipped
  for (int i = 0; i < lines.size(); ++i) {
    string current_line = lines[i];
    if (current_line == "") {
      sums.push_back(current_sum);
      current_sum = 0;
    } else {
      current_sum += stoi(current_line);
    }
  }

  int res = getMaxValFromVector(sums);
  cout << "EXC 1A:\t" << res << endl;
}
