#include <cmath>
#include <limits>
#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string result;
  if (x == 0) {
    return "0";
  }

  if (x == std::numeric_limits<int>::min()) {
      return "-2147483648";
  }

  if (x < 0) {
    result.push_back('-');
    x = -x;
  }

  int n_digits = (int) floor(log10(x)) + 1;
  int d;
  for (int i = 0; i < n_digits; ++i) {
    d = (int) (x / (int) pow(10, n_digits - i - 1)) % 10;
    result.push_back(d + '0');
  }

  return result;
}

int StringToInt(const string& s) {
  int result = 0;
  bool neg = false;
  for (char c : s) {
    if (c == '-') {
      neg = true;
    }
    else if (c == '+') {
      neg = false;
    }
    else {
      result = (result * 10) + (c - '0');
    }
  }

  return neg ? -result : result;
}

void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
