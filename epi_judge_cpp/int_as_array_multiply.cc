#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // naive solution - work out negative signs up front
  if ((num1 == vector<int> {0}) ||
      (num2 == vector<int> {0})) {
    return vector<int> {0};
  }

  bool neg = (num1[0] < 0) ^ (num2[0] < 0);
  num1[0] = (int) abs(num1[0]);
  num2[0] = (int) abs(num2[0]);

  int tmp;
  int carry;
  vector<int> res(num1.size() + num2.size());
  for (int n = num1.size(); n > 0; --n) {
    carry = 0;
    for (int m = num2.size(); m > 0; --m) {
      tmp = num1[n - 1] * num2[m - 1] + res[n + m - 1] + carry;
      res[n + m - 1] = tmp % 10;
      carry = (int) tmp / 10;
    }
    res[n - 1] = carry;
  }

  if (res[0] == 0) {
    res.erase(res.begin());
  }

  if (neg) {
    res[0] *= -1;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
