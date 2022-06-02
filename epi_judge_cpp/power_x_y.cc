#include "test_framework/generic_test.h"
#include <cmath>

// given: a double x, and and integer y
// unknown: the double value that represents x raised to the y-th power
double Power(double x, int y) {
  double res = 1.0;

  for (int i = 0; i * i < y * y; ++i) {
    res *= (y < 0) ? (1.0 / x) : x;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
