#include <cstdlib>
#include <iostream>

#include "./debug.h"
#include "./matrix.h"

int main() {
  Matrix<2, 2> a;
  for (auto it = a.begin(); it != a.end(); ++it) {
    *it = rand() % 10;
  }
  a.print();
  std::cout << '\n';
  Matrix<2, 3> b;
  for (auto it = b.begin(); it != b.end(); ++it) {
    *it = rand() % 10;
  }
  b.print();
  std::cout << '\n';
  Matrix<2, 3> c = a * b;
  c.print();
  std::cout << "-------------------------\n";
  Matrix<10, 10, int> A;
  for (auto it = A.begin(); it != A.end(); ++it) {
    *it = rand() % 10;
  }
  A.print();
  std::cout << '\n';
  Matrix<10, 10, int> B;
  for (auto it = B.begin(); it != B.end(); ++it) {
    *it = rand() % 10;
  }
  B.print();
  std::cout << '\n';
  Matrix<10, 10, int> C = A * B;
  C.print();
}
