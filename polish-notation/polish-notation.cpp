
#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

string reverse_notation(string input) {

  stack<char> stack;
  string output_string, new_number_string;
  map<char, int> character_priorities{{'(', 1}, {')', 1}, {'-', 2},
                                      {'+', 2}, {'*', 3}, {'/', 3}};

  string::iterator p_end_number;

  for (string::iterator it = input.begin(); it != input.end();) {

    if (isdigit(*it)) {

      new_number_string = *it;
      p_end_number = it;

      while (++p_end_number != input.end() && isdigit(*p_end_number)) {
        new_number_string += *p_end_number;
      }

      output_string += new_number_string + ' ';

      it = p_end_number;
      continue;
    }

    if (*it == '(') {
      stack.push(*it++);
      continue;
    }

    else if (*it == ')') {

      while (stack.top() != '(' && !stack.empty()) {
        output_string += stack.top();
        output_string += ' ';
        stack.pop();
      }

      stack.pop();

      it++;
      continue;
    }

    if (stack.empty() || character_priorities.find(*it)->second >
                             character_priorities.find(stack.top())->second) {
      stack.push(*it++);
      continue;
    }

    else if (character_priorities.find(stack.top())->second >=
             character_priorities.find(*it)->second) {

      output_string += stack.top();
      output_string += ' ';
      stack.pop();

      while (!stack.empty() &&
             (character_priorities.find(stack.top())->second >=
              character_priorities.find(*it)->second)) {
        output_string += stack.top();
        output_string += ' ';
        stack.pop();
      }

      if (stack.empty() || character_priorities.find(*it)->second >
                               character_priorities.find(stack.top())->second) {
        stack.push(*it++);
        continue;
      }
    }
  }

  if (!stack.empty()) {
    while (!stack.empty()) {
      output_string += stack.top();
      output_string += ' ';
      stack.pop();
    }
  }

  return output_string;
}

int calculate_reverse_notation(string input) {

  stack<int> stack;
  string new_number_string;

  string::iterator p_end_number;

  int number_1, number_2;
  int output_int;

  for (string::iterator it = input.begin(); it != input.end(); ++it) {

    if (isdigit(*it)) {

      new_number_string = *it;
      p_end_number = it;

      while (++p_end_number != input.end() && *p_end_number != ' ') {
        new_number_string += *p_end_number;
      }

      it = p_end_number;

      stack.push(stoi(new_number_string));
    }

    else {

      number_1 = stack.top();
      stack.pop();
      number_2 = stack.top();
      stack.pop();

      if (*it == '*') {
        stack.push(number_2 * number_1);
      }

      else if (*it == '/') {
        stack.push(number_2 / number_1);
      }

      else if (*it == '+') {
        stack.push(number_2 + number_1);
      }

      else if (*it == '-') {
        stack.push(number_2 - number_1);
      }

      ++it;
    }
  }

  return stack.top();
}

int main() {
  string str = "123*(1222-12354)*93";
  cout << reverse_notation(str) << endl;
  cout << calculate_reverse_notation(reverse_notation(str));
}
