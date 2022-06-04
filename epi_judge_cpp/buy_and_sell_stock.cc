#include <algorithm>
#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::min;
using std::max;

// optimal one-pass - Because we are only allowed to sell the stock after we
//                    buy it, we only need to consider forward differences.
//                    In searching for the max profit, we keep track of the
//                    minimum price seen so far.
//
double BuyAndSellStockOnce(const vector<double>& prices) {
  double lowest = std::numeric_limits<double>::infinity();
  double max_profit = 0.0;

  for (double price : prices) {
    lowest = min(price, lowest);
    max_profit = max(price - lowest, max_profit);
  }

  return max_profit;
}

// brute force
//
// double BuyAndSellStockOnce(const vector<double>& prices) {
//   double max = 0.0;
//
//   for (int i = 0; i < prices.size(); ++i) {
//     for (int j = i + 1; j < prices.size(); ++j) {
//       double profit = prices[j] - prices[i];
//       max = profit > max ? profit : max;
//     }
//   }
//
//   return max;
// }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
