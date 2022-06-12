#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;
void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  unordered_set<int> visited;

  int idx = 0;
  int cycle, tmp1, tmp2;
  while (visited.size() < A.size()) {
    if (visited.find(idx) != visited.end()) {
      ++idx;
    }
    else { // we have reached an unvisited index, let's begin a cycle here
      cycle = idx;
      tmp1 = A[cycle];
      while (perm[cycle] != idx) {
        tmp2 = A[perm[cycle]];
        A[perm[cycle]] = tmp1;
        tmp1 = tmp2;
        cycle = perm[cycle];
        visited.insert(cycle);
      }
      A[idx] = tmp1;
      visited.insert(idx);
    }
  }

  return;
}
vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
