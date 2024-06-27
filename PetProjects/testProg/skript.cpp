#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  // std::string out = / sys / class / power_supply / BAT0 / status;
  // std::cout << out;
  int a = std::system("/sys/class/power_supply/BAT0/status");
  std::cout << a;
  return 0;
}
