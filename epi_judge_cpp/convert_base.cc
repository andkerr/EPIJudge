<<<<<<< HEAD
#include <cmath>
#include <iostream>
#include <unordered_map>
=======
#include <cassert>
#include <iostream>
>>>>>>> 9e8388b76019cd845e819d58e939174e4f5e0974
#include <string>

#include "test_framework/generic_test.h"
using std::unordered_map;
using std::string;

int getDigit(char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  }
  else if ('A' <= c && c <= 'F') {
    return c - 55; // (int) 'A' = 65;
  }
  else {
    std::cout << (int) c << "\n";
    assert(false);
  }
}

char getChar(int n) {
  if (0 <= n && n <= 9) {
    return '0' + n;
  }
  else if (10 <= n && n <= 15) {
    return 'A' + (n - 10);
  }
  else {
    assert(false);
  }
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
<<<<<<< HEAD
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
=======
  if (num_as_string == "0") {
    return "0";
  }

  bool negative = false;
  int b10 = 0;
  int base_power = 1;

  char c;
  int k = num_as_string.size();
  for (int i = 0; i < k; ++i) {
    c = num_as_string[k - i - 1];
    if (c == '-') {
      negative = true;
    }
    else {
      b10 += (getDigit(c) * base_power);
      base_power *= b1;
    }
  }

  string result;
  while (b10) {
    result.push_back(getChar(b10 % b2));
    b10 = (int) (b10 / b2);
  }
  if (negative) {
    result.push_back('-');
  }

  return string(result.rbegin(), result.rend());
>>>>>>> 9e8388b76019cd845e819d58e939174e4f5e0974
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
