
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <unordered_map>
#pragma once

using namespace std;

enum states { H, ID, NM, ASGN, DLM, ERR };

class Lexer {
 public:
  ifstream file_txt;

  vector<string> name_states{"H", "ID", "NM", "ASGH", "DLM", "ERR"};
  vector<string> key_words{"for", "do"};
  vector<pair<string, states>> all_token;
  string new_token;
  states current_state = H;
  string spacers = "\t\n ";
  string comparative_signs = "();<>=";

  const int count_key_words = 2;
  char new_char;

  unordered_map<states, void (Lexer::*)()> state_transition{

      {H, &Lexer::current_state_is_H},
      {ID, &Lexer::current_state_is_ID},
      {ASGN, &Lexer::current_state_is_ASGN},
      {DLM, &Lexer::current_state_is_DLM},
      {NM, &Lexer::current_state_is_NM},
      {ERR, &Lexer::current_state_is_ERR}};

 public:
  Lexer(string name_file_txt);

  char fgetc();

  bool is_num();

  bool is_kword();

  void add_token();

  void next_state();

  void current_state_is_H();

  void current_state_is_ID();

  void current_state_is_ASGN();

  void current_state_is_DLM();

  void current_state_is_NM();

  void current_state_is_ERR();

  void show_all_token();
};
