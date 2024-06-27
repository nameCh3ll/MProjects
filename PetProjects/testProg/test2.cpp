#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  const size_t len_number = pow(10, 13);
  const size_t N = 100000;
  unsigned long long value;

  vector<unsigned long long> F{0, 1, 2, 3};

  for (size_t i = F.size() - 1; i != 25; ++i) {
    F.push_back(F[i] * 2 % len_number);
  }
  for (size_t i = 0; i < 2; ++i) {
    value = 0ull;
    for (auto it = F.end() - 25; it < F.end(); it += 2) {
      value += *it;
    }
    F.push_back(value);
  }
  for (size_t i = F.size(); i != N + 1; ++i) {
    value = ((F[i - 1] + F[i - 2] + len_number) - F[i - 27] % len_number) %
            len_number;
    F.push_back(value);
  }
  cout << to_string(F[N]).size() << '\t' << F[N] << '\n';
  return 1;
}
