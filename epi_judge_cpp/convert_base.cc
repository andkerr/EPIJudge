#include <cassert>
#include <iostream>
#include <string>

#include "test_framework/generic_test.h"
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
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
