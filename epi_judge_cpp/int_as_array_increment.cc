#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int idx = A.size() - 1;
  int tmp = A[idx] + 1;
  A[idx--] = tmp % 10;
  int carry = (tmp >= 10);

  while (carry && idx >= 0) {
    tmp = A[idx] + carry;
    A[idx] = tmp % 10;
    carry = (tmp >= 10);
    --idx;
  }

  if (carry) {
    A[0] = 1;
    A.push_back(0);
  }

  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
