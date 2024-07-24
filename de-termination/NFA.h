#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "state.h"

#pragma once

using namespace std;

class NFA {
  int initial_states;
  int final_states;

  vector<string> all_name_state;
  vector<string> all_alphabet;

  unordered_map<string, state*> all_states;
  unordered_map<state*, string> p_all_states;

  unordered_map<string, state*> DFA;
  unordered_map<state*, string> p_DFA;

 public:
  NFA(const string& all_alphabet, const string& all_name_state,
      const string& name_start_state, const string& name_end_state);

  void add_new_link(const string& name_state_from, const string& if_letter,
                    const string& name_state_in);

  void show_all_states();

  void set_all_name_state(string all_name_state);

  void set_all_alphabet(string all_alphabet);

  void create_DFA();

  void show_pointers();

  void set_start_state(const string& name_state);

  void set_end_state(const string& name_state);

  void delete_empty_states();

  void set_links(const string& links);

  void get_end_state();

  void get_start_state();
};
