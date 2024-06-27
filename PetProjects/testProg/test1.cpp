#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<int> sum_count(73);

unsigned int f(unsigned int n) {
  if (n <= 1) return 1;
  return n * f(n - 1);
}

void CombinationRepetitionUtil(vector<int> &chosen, vector<int> &arr, int index,
                               int r, int start, int end) {
  if (index == r) {
    size_t sum_value = accumulate(chosen.cbegin(), chosen.cend(), 0);
    size_t tmp_sum =
        f(6) /
        accumulate(arr.cbegin(), arr.cend(), 1, [&chosen](int lhs, int rhs) {
          return lhs * f(count(chosen.cbegin(), chosen.cend(), rhs));
        });
    sum_count[sum_value] += tmp_sum;
    return;
  }

  for (size_t i = start; i <= end; ++i) {
    chosen[index] = i;
    CombinationRepetitionUtil(chosen, arr, index + 1, r, i, end);
  }
  return;
}

void CombinationRepetition(vector<int> &arr) {
  vector<int> chosen(arr.size() / 2);
  CombinationRepetitionUtil(chosen, arr, 0, arr.size() / 2, 0, arr.size() - 1);
}

int main() {
  vector<int> arr{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  CombinationRepetition(arr);
  cout << 13 * accumulate(sum_count.cbegin(), sum_count.cend(), 0ll,
                          [](unsigned long long lhs, int rhs) {
                            return lhs + pow(rhs, 2);
                          });

  return 0;
}
