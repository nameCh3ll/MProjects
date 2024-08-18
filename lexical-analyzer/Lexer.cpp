
#include "Lexer.h"

Lexer::Lexer(string name_file_txt) {
  file_txt.open(name_file_txt);

  if (!file_txt.is_open()) {
    cout << "File opening error\n";
  }

  else {
    fgetc();
    while (!file_txt.eof()) {
      next_state();
    }
  }
}

char Lexer::fgetc() {
  file_txt.get(new_char);
  return new_char;
}

bool Lexer::is_num() {
  if (new_token.empty()) {
    return false;
  }

  else {
    int count_numbers = accumulate(new_token.cbegin(), new_token.cend(), 0,
                                   [](int answer, const char current) {
                                     return ('0' <= current && current <= '9')
                                                ? ++answer
                                                : answer;
                                   });
    int count_sum_simbol = accumulate(
        new_token.cbegin(), new_token.cend(), 0,
        [](int answer, const char current) {
          return (current == '-' || current == '+') ? ++answer : answer;
        });
    int count_e = accumulate(new_token.cbegin(), new_token.cend(), 0,
                             [](int answer, const char current) {
                               return (current == 'E' || current == 'e')
                                          ? ++answer
                                          : answer;
                             });
    int count_dot = accumulate(new_token.cbegin(), new_token.cend(), 0,
                               [](int answer, const char current) {
                                 return (current == '.') ? ++answer : answer;
                               });

    auto p_e = find(new_token.cbegin(), new_token.cend(), 'e');
    auto p_dot = find(new_token.cbegin(), new_token.cend(), '.');

    if ((count_numbers !=
         (new_token.size() - (count_sum_simbol + count_e + count_dot))) ||
        count_sum_simbol > 2 || count_e > 1 || count_dot > 1) {
      return false;
    }

    else if (((count_sum_simbol == 1 &&
               ((new_token[0] == '+' || new_token[0] == '-') ||
                (count_e == 1 && (p_e + 1) != new_token.end() &&
                 ((*(p_e + 1) == '+') || *(p_e + 1) == '-')))) ||

              (count_sum_simbol == 2 &&
               (new_token[0] == '+' || new_token[0] == '-') &&
               (count_e == 1 && (p_e + 1) != new_token.end() &&
                ((*(p_e + 1) == '+') || *(p_e + 1) == '-'))) ||
              count_sum_simbol == 0) &&

             (p_dot < p_e || count_dot == 0)) {
      return true;
    }

    else
      return false;
  }

  /*else if (!(count_dot == 1))
  bool flag_e = true;

  if ((new_token.size() >= 2 && '0' <= new_token[0] && new_token[0] <= '9' &&
  new_token[1] == '.') ||) {

          for (auto iterator = new_token.begin() + 2; iterator !=
  new_token.end(); ++iterator) {

                  if ('0' <= *iterator && *iterator <= '9') { continue; }

                  else if ((*iterator == 'e' || *iterator == 'E') && flag_e) {
  flag_e == false; continue; }

                  else
          }
  }*/
}

bool Lexer::is_kword() {
  return ((find(key_words.cbegin(), key_words.cend(), new_token) !=
           key_words.cend()) ||
          find_if(new_token.cend(), new_token.cend(), [](const char &curent) {
            return !(('A' <= curent && curent <= 'z' &&
                      !('[' <= curent && curent <= '`')) ||
                     curent == '_');
          }) == new_token.cend());
}

void Lexer::show_all_token() {
  string new_string;

  cout << "_____________________________________________\n";
  cout << "|       Lexem       |       Lexeme type     |\n";
  cout << "|-------------------|-----------------------|\n";

  for (const auto &token : all_token) {
    new_string = "| " + token.first + string(20, ' ');
    new_string.resize(20);
    new_string += "| " + name_states[token.second] + string(20, ' ');
    new_string.resize(44);
    new_string += '|';
    cout << new_string << endl;
    cout << "|-------------------|-----------------------|\n";
    // cout << "| " << token.first  << "\t\t\t" << name_states[token.second] <<
    // endl;
    //"| for               | ID                    |"
  }
}

void Lexer::current_state_is_H() {
  // cout << "current_state_is_H" << endl;

  while (spacers.find(new_char) != string::npos && !file_txt.eof()) {
    fgetc();
  };

  // cout << new_char << endl;

  if (new_char == ':') {
    new_token = new_char;
    current_state = ASGN;
    fgetc();
  }

  else if (('A' <= new_char && new_char <= 'z' &&
            !('[' <= new_char && new_char <= '`')) ||
           (new_char == '_')) {
    new_token = new_char;
    current_state = ID;
    fgetc();
  }

  else if (('0' <= new_char && new_char <= '9') ||
           ('+' <= new_char && new_char <= '.' && new_char != ',')) {
    new_token = new_char;
    current_state = NM;
    fgetc();
  }

  else {
    new_token = new_char;
    current_state = DLM;
  }
}

void Lexer::current_state_is_ID() {
  // cout << "current_state_is_ID" << endl;

  while (('A' <= new_char && new_char <= 'z' &&
          !('[' <= new_char && new_char <= '`')) ||
         (('0' <= new_char && new_char <= '9')) || (new_char == '_')) {
    new_token += new_char;
    fgetc();
  }

  // cout << new_token << endl;

  if (is_kword())
    add_token();

  current_state = H;
}

void Lexer::current_state_is_ASGN() {
  // cout << "current_state_is_ASGN" << endl;
  cout << new_char << endl;

  if (new_char == '=') {
    new_token += new_char;
    add_token();
    current_state = H;
    fgetc();
  }

  else {
    current_state = ERR;
    fgetc();
  }
}

void Lexer::current_state_is_DLM() {
  // cout << "current_state_is_DLM" << endl;
  // cout << new_char << endl;

  if (comparative_signs.find(new_char) != string::npos) {
    add_token();
    current_state = H;
    fgetc();
  }

  else {
    current_state = ERR;
  }
}

void Lexer::current_state_is_NM() {
  // cout << "current_state_is_NM" << endl;

  while (('+' <= new_char && new_char <= '9' && new_char != ',' &&
          new_char != '/') ||
         (new_char == 'e') || (new_char == 'E')) {
    new_token += new_char;
    fgetc();
  }

  if (!is_num()) {
    current_state = ERR;
  }

  else {
    add_token();
    current_state = H;
  }
}

void Lexer::add_token() {
  all_token.push_back(make_pair(new_token, current_state));
}

void Lexer::current_state_is_ERR() { /*cout << "current_state_is_ERR" << endl;*/
  current_state = H;
  fgetc();
}

void Lexer::next_state() {
  (this->*state_transition.find(current_state)->second)();
}
