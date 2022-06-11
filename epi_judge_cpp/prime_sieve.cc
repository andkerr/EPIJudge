#include <deque>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::deque;

// Given n, return all primes up to and including n.
// Sieve of Eratosthenes
// 1 - Initialize an array representing 1 to n
// 2 - For each new prime encountered, cross of its multiples
//     up to and including n.
vector<int> GeneratePrimes(int n) {
  vector<int> res;
  deque<bool> is_prime(n, true); // indices 0 -> (n - 1), primes 1 -> n
  is_prime[0] = false;

  for (int i = 2; i <= n; ++i) {
    if (is_prime[i - 1]) {
      for (int j = 2; j * i <= n; ++j) {
        is_prime[j * i - 1] = false;
      }
    }
  }

  for (int i = 0; i < is_prime.size(); ++i) {
    if (is_prime[i]) {
      res.push_back(i + 1);
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
