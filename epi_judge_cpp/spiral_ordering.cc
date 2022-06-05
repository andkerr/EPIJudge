#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// brute force - traverse the matrix in spiral order, incrementing a layer
//               variable.
//
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  vector<int> res;
  int n = square_matrix.size();
  int r, c;

  for (int layer = 0; layer < static_cast<int>(n / 2); ++layer) {
    r = layer;
    c = layer;

    // traverse top edge L to R
    for ( ; c < n - layer - 1; ++c) {
      res.emplace_back(square_matrix[r][c]);
    }
    // traverse down right edge
    for ( ; r < n - layer - 1; ++r) {
      res.emplace_back(square_matrix[r][c]);
    }
    // traverse bottom edge R to L
    for ( ; c > layer; --c) {
      res.emplace_back(square_matrix[r][c]);
    }
    // traverse up left edge
    for ( ; r > layer; --r) {
      res.emplace_back(square_matrix[r][c]);
    }
  }
  // add center element if n is odd
  if (n % 2) {
    res.emplace_back(square_matrix[static_cast<int>(n / 2)][static_cast<int>(n / 2)]);
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
