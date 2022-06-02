#include "test_framework/generic_test.h"

const int lookup[16] = {0, 8, 4, 12,
                        2, 10, 6, 14,
                        1, 9, 5, 13,
                        3, 11, 7, 15};

// brute force 2 - iterate through the 32 LSB, swapping each with the
//                 corresponding MSB
//unsigned long long ReverseBits(unsigned long long x) {
//  for (int i = 0; i < 32; ++i) {
//    int j = 64 - i - 1;
//    if (((x >> i) & 1) != ((x >> j) & 1)) {
//      unsigned long long mask = (1L << i) | (1L << j);
//      x ^= mask;
//    }
//  }
//
//  return x;
//}

// brute force - iterate through all 64 bits and store them in a new variable
//               in reverse order.
unsigned long long ReverseBits(unsigned long long x) {
  unsigned long long res = 0;

  // Avoid while (x) here. If x is left-padded with empty bits, the result won't
  // have the correct number of right-padding empty bits, i.e. it will be small.
  for (int i = 0; i < 64; ++i) {
    res = (res << 1) + (x & 1);
    x >>= 1;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
