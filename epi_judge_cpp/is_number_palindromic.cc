#include "test_framework/generic_test.h"

int len(int x) {
  return (int) floor(log10(x) + 1);
}

int digit(int x, int idx) {
  return (int) (x / pow(10, idx)) % 10;
}

bool IsPalindromeNumber(int x) {
  if (x < 0) {
    return false;
  }

  int n_digits = len(x);
  for (int i = 0; i < n_digits / 2; ++i) {
    if (digit(x, i) != digit(x, n_digits - i - 1)) {
      return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
