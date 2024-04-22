#include "./debug.h"
#include "./matrix.h"
#include <cstdlib>

using namespace std;

void f(int a) { cout << __PRETTY_FUNCTION__ << '\n'; }

int main() {

  Matrix<10, 10> a;
  // Matrix<10, 10> b(a);
  // for (auto it = a.begin(); it != a.end(); ++it) {
  //   *it = rand() % 10;
  // }
  for (auto it = a.begin(); it != a.end(); ++it) {
    cout << *it << '\n';
  }
  return 1;
}
