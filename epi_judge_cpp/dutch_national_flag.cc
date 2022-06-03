#include <algorithm>
#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
using std::swap;
enum class Color { kRed, kWhite, kBlue };

// optimal, 1 pass
//
void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  vector<Color>& A = *A_ptr;
  int lo = 0;
  int eq = 0;
  int hi = A.size();
  Color pivot = A[pivot_index];
  while (eq < hi) {
    if (A[eq] < pivot) {
      swap(A[lo++], A[eq++]);
    }
    else if (A[eq] > pivot) {
      swap(A[eq], A[--hi]);
    }
    else {
      ++eq;
    }
  }
}

// brute force - Treat this as two instances of partioning an array of two values.
//               First, partition the array into [< pivot | >= pivot]. Then,
//               operate on the rightmost section to separate elements that
//               equal the pivot from those that are greater than the pivot.
// void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
//   vector<Color>& A = *A_ptr;
//   Color pivot = A[pivot_index];
//   int lo = 0;
//   int hi = A.size() - 1;
//   while (lo < hi) {
//     if (A[lo] >= pivot) {
//       swap(A[lo], A[hi]);
//       hi -= 1;
//     }
//     else {
//       lo += 1;
//     }
//   }
// 
//   int eq = lo;
//   hi = A.size() - 1;
//   while (eq < hi) {
//     if (A[eq] > pivot) {
//       swap(A[eq], A[hi]);
//       hi -= 1;
//     }
//     else {
//       eq += 1;
//     }
//   }
// 
//   return;
// }

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
