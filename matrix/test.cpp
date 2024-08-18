#include <cstdlib>

#include "./debug.h"
#include "./matrix.h"

int main() {
  Matrix<2, 3> a;
  for (auto it = a.begin(); it != a.end(); ++it) {
    *it = rand() % 10;
  }
  a.print();
  std::cout << std::endl;
  Matrix<3, 2> b(a);
  b.print();
  std::cout << std::endl;
  Matrix<2, 2> c = a * b;
  c.print();
}
