#include <cmath>
#include <iostream>
#include <unordered_map>
#include <string>

#include "test_framework/generic_test.h"
using std::unordered_map;
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  unordered_map<char, int> get_digit = {
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15}
  };

  unordered_map<int, char> get_char;
  for (auto keyVal : get_digit) {
    get_char[keyVal.second] = keyVal.first;
  }

  int power = 1;
  int b10 = 0;
  int k = num_as_string.size();
  for (int i = 0; i < k; ++i) {
    b10 = (b10 * 10) + (get_digit[num_as_string[k - i - 1]] * power);
    power *= b1;
  }

  std::cout << b10 << "\n";

  string result;
  while (b10) {
    result.push_back(get_char[b10 % b2]);
    b10 /= b2;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
