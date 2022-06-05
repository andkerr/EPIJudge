#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  int width = partial_assignment[0].size();
  int height = partial_assignment.size();
  int r, c, elt;
  unordered_set<int> seen;

  // check rows
  for (r = 0; r < height; ++r) {
    seen.clear();
    for (c = 0; c < width; ++c) {
      elt = partial_assignment[r][c];
      if (elt && seen.find(elt) != seen.end()) {
        return false;
      }
      seen.insert(elt);
    }
  }

  // check columns
  for (c = 0; c < width; ++c) {
    seen.clear();
    for (r = 0; r < height; ++r) {
      elt = partial_assignment[r][c];
      if (elt &&
          seen.find(elt) != seen.end()) {
        return false;
      }
      seen.insert(elt);
    }
  }

  int box_r = 0, box_c = 0;
  // check squares
  for (r = 0; r * 3 < height; ++r) {
    for (c = 0; c * 3 < width; ++c) {
      seen.clear();
      for (box_r = 0; box_r < 3; ++box_r) {
        for (box_c = 0; box_c < 3; ++box_c) {
          elt = partial_assignment[r * 3 + box_r][c * 3 + box_c];
          if (elt &&
              seen.find(elt) != seen.end()) {
            return false;
          }
          seen.insert(elt);
        }
      }
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
