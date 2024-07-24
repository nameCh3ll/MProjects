#include <iostream>
#include <unordered_map>
#include <vector>

#pragma once

using namespace std;

class state {
 public:
  unordered_multimap<state*, string> next_states;

  bool flag = false;
  bool end_state = false;
  bool start_state = false;

  state();

  state(string if_letter, state* link_state = nullptr);

  void link(state* name_state, string if_letter);
};
