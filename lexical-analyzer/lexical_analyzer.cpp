
#include <iostream>

#include "Lexer.h"

int main() {
  setlocale(LC_ALL, "RUS");
  Lexer lexer("input.txt");
  lexer.show_all_token();
}
