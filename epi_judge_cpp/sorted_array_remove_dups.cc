#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;

  // tracks the location where the next unique value will be written, and the
  // total number of unique elements found
  int valid = 0;

  int curr;
  for (int hi = 0; hi < A.size(); ++hi) {
    if (hi == 0 || A[hi] != curr) { // found new value
      A[valid] = A[hi];
      curr = A[hi];
      ++valid;
    }
  }

  return valid;
}

vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
