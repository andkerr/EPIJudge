#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::iota;
using std::vector;

// optimized - use a hash table to keep track of swapped indices only. This
//             achieves better performance for k << n.
vector<int> RandomSubset(int n, int k) {
  std::unordered_map<int, int> swaps;
  std::mt19937 gen((std::random_device())());
  int idx;
  for (int i = 0; i < k; ++i) {
    idx = std::uniform_int_distribution<int> {i, n - 1}(gen);
    auto it1 = swaps.find(i);
    auto it2 = swaps.find(idx);
    if (it1 == swaps.end() && it2 == swaps.end()) {
      swaps[i] = idx;
      swaps[idx] = i;
    }
    else if (it1 == swaps.end() && it2 != swaps.end()) {
      swaps[i] = swaps[idx];
      swaps[idx] = i;
    }
    else if (it1 != swaps.end() && it2 == swaps.end()) {
      swaps[idx] = swaps[i];
      swaps[i] = idx;
    }
    else {
      int tmp = swaps[i];
      swaps[i] = swaps[idx];
      swaps[idx] = tmp;
    }
  }

  vector<int> result;
  for (int i = 0; i < k; ++i) {
    result.push_back(swaps[i]);
  }

  return result;
}

// naive initial solution - initialize and array of values [0...n-1], and store
//                          a subset by swapping into the first k elements. This
//                          requires O(n) space and O(n) time to create the initial
//                          array, and O(k) time to construct the subset. We can
//                          do better!
//vector<int> RandomSubset(int n, int k) {
//  vector<int> nums;
//  for (int i = 0; i < n; ++i) {
//    nums.push_back(i);
//  }
//
//  std::mt19937 gen((std::random_device())());
//  for (int i = 0; i < k; ++i) {
//    std::swap(nums[i], nums[std::uniform_int_distribution<int> {i, n - 1}(gen)]);
//  }
//
//  return vector<int>(nums.begin(), nums.begin() + k);
//}
bool RandomSubsetRunner(TimedExecutor& executor, int n, int k) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(back_inserter(results), 100000,
                    std::bind(RandomSubset, n, k));
  });

  int total_possible_outcomes = BinomialCoefficient(n, k);
  vector<int> A(n);
  iota(begin(A), end(A), 0);
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(n, k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, n, k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSubsetWrapper(TimedExecutor& executor, int n, int k) {
  RunFuncWithRetries(bind(RandomSubsetRunner, std::ref(executor), n, k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n", "k"};
  return GenericTestMain(args, "random_subset.cc", "random_subset.tsv",
                         &RandomSubsetWrapper, DefaultComparator{},
                         param_names);
}
