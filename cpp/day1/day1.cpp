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
      cout << "curr max vak\t" << max_val << "\tcurr vec entry:\t" << vec[i]
           << endl;
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
  file.open(file_path);
  while (getline(file, read)) {
    lines.push_back(read);
  }
  return lines;
}

class Backpack {
private:
  vector<int> cal_numbers;

public:
  void append(int ip) { cal_numbers.push_back(ip); }
  int sum() { return sumOverVectorElements(cal_numbers); }
};

int main() {

  string path = "./day1/input_test.txt";

  vector<string> lines = extractPathToLineVector(path);
  int current_sum{0};
  vector<int> sums;

  for (int i = 0; i < lines.size(); ++i) {
    string current_line = lines[i];
    if (current_line == "") {
      sums.push_back(current_sum);
      current_sum = 0;
    } else {
      current_sum += stoi(current_line);
    }
  }

  printAllVectorEntries(sums);
  int res = getMaxValFromVector(sums);
  cout << "EXC 1A:\t" << res << endl;
}
