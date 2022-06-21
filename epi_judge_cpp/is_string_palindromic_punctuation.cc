#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
using std::string;
using std::tolower;

bool IsPalindrome(const string& s) {
  int lo = 0;
  int hi = s.size() - 1;

  while (lo < hi) {
    while (!isalnum(s[lo]) && lo < hi) {
      ++lo;
    }
    while (!isalnum(s[hi]) && lo < hi) {
      --hi;
    }
    if (tolower(s[lo++]) != tolower(s[hi--])) {
      return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
