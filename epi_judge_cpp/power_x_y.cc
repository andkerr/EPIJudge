#include "test_framework/generic_test.h"
#include <cmath>

// recursive
//
// double Power(double x, int y) {
//   if (y == 0) {
//     return 1.0;
//   }
//
//   if (y < 0) {
//     y = -y;
//     x = 1 / x;
//   }
//
//   double partial = Power(x, y >> 1);
//   if (y & 1) {
//     return partial * partial * x;
//   }
//   else {
//     return partial * partial;
//   }
// }

// optimized iterative
//
double Power(double x, int y) {
  double res = 1.0;
  long long power = y; // guard against y == INT_MIN

  if (power < 0) {
    power = -power;
    x = 1 / x;
  }

  while (power) {
    if (power & 1) {
      res *= x;
    }
    x *= x;
    power >>= 1;
  }

  return res;
}

// naive
//
// double Power(double x, int y) {
//   double res = 1.0;
//
//   for (int i = 0; i * i < y * y; ++i) {
//     res *= (y < 0) ? (1.0 / x) : x;
//   }
//   return res;
// }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
