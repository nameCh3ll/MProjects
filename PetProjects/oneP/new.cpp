#include <cmath>
#include <iostream>
#include <vector>

void multi(std::vector<int> &a, std::vector<int> &b) {
  int sum_tmp = 0;
  std::vector<int> tmp;
  int ost;
  for (size_t i = 0; i < b.size(); ++i) {
    ost = 0;
    for (size_t g = 0; g < a.size() - 1; ++g) {
      ost += (a[i] * b[g]);
      tmp.push_back(ost % 10);
      ost /= 10;
    }
  }
}

void f() { std::vector<int> number{1}; }
int main() { return 1; }
