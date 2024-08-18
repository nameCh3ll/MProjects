#include "NFA.h"

NFA::NFA(const string &all_alphabet, const string &all_name_state,
         const string &name_start_state, const string &name_end_state) {
  string new_string;
  state *new_state;
  this->initial_states = initial_states;
  this->final_states = final_states;

  for (auto iterator = all_alphabet.cbegin();; ++iterator) {
    new_string = "";

    while (iterator != all_alphabet.cend() && *iterator != ' ') {
      new_string += *iterator++;
    }

    this->all_alphabet.push_back(new_string);

    if (iterator == all_alphabet.cend())
      break;
  }

  for (auto iterator = all_name_state.cbegin();; ++iterator) {
    new_string = "";

    while (iterator != all_name_state.cend() && *iterator != ' ') {
      new_string += *iterator++;
    }

    this->all_name_state.push_back(new_string);

    if (iterator == all_name_state.cend())
      break;
  }

  for (auto iterator = (this->all_name_state).cbegin();
       iterator != (this->all_name_state).cend(); ++iterator) {
    /*cout << *iterator << '\t' << new state() << endl;*/

    new_state = new state();

    DFA.insert(make_pair(*iterator, new_state));
    p_DFA.insert(make_pair(new_state, *iterator));

    new_state = new state();

    all_states.insert(make_pair(*iterator, new_state));
    p_all_states.insert(make_pair(new_state, *iterator));
  }

  int count = pow(2, this->all_name_state.size());
  unsigned int mask = 0x00000000;

  for (int i = 0; i < count - 1; ++i) {
    mask += 1;

    new_string = "";

    for (int g = 0; g < this->all_name_state.size(); ++g) {
      if ((mask & (1 << g)) >> g == 1)
        new_string += this->all_name_state[g];
    }

    if (new_string.size() != 1) {
      new_state = new state();

      this->all_name_state.push_back(new_string);

      if (new_string.find(name_end_state) != string::npos) {
        new_state->end_state = true;
      }

      DFA.insert(make_pair(new_string, new_state));
      p_DFA.insert(make_pair(new_state, new_string));

      new_state = new state();

      all_states.insert(make_pair(new_string, new_state));
      p_all_states.insert(make_pair(new_state, new_string));
    }
  }

  set_end_state(name_end_state);
  DFA[name_start_state]->start_state = true;
  DFA[name_start_state]->flag = true;
}

void NFA::add_new_link(const string &name_state_from, const string &if_letter,
                       const string &name_state_in) {
  // cout << all_states[name_state_from] << '\t' << all_states[name_state_in] <<
  // '\t' << if_letter << endl;

  all_states[name_state_from]->link(all_states[name_state_in], if_letter);
}

void NFA::show_all_states() {
  for (auto &iterator : DFA) {
    if (iterator.second != nullptr) {
      cout << iterator.first /*<< '\t' << iterator.second*/ << endl;

      for (auto &iterator_2 : iterator.second->next_states) {
        cout << "  " << p_DFA[iterator_2.first] << "  "
             << iterator_2.second /* << '\t' << iterator_2.first */ << endl;
      }

      cout << endl;
    }
  }
}

void NFA::set_all_name_state(string all_name_state) {
  string new_name_state;

  auto new_char = all_name_state.cbegin();

  while (new_char++ != all_name_state.cend()) {
    new_name_state = "";

    while (*new_char != ' ' && new_char != all_name_state.cend())
      new_name_state += *new_char;

    this->all_name_state.emplace_back(new_name_state);
  }
}

void NFA::set_all_alphabet(string all_alphabet) {
  string new_letter;

  auto new_char = all_alphabet.cbegin();

  while (new_char++ != all_alphabet.cend()) {
    new_letter = "";

    while (*new_char != ' ' && new_char != all_alphabet.cend())
      new_letter += *new_char;

    this->all_alphabet.emplace_back(new_letter);
  }
}

void NFA::create_DFA() {
  unordered_map<string, string> if_letterName_state;
  set<int> int_set;
  string new_string;

  for (auto &current_state : all_states) {
    if (current_state.first.size() == 1) {
      for (auto &current_if_letter : all_alphabet) {
        for (auto &next_state : current_state.second->next_states) {
          if (next_state.second == current_if_letter)
            if_letterName_state[current_if_letter] +=
                p_all_states[next_state.first];
        }
      }

      for (auto &i : if_letterName_state) {
        // cout << current_state.first << '\t' << i.first << '\t' << i.second <<
        // '\t' << all_states[i.second] << endl;
        new_string = "";

        for (auto &g : i.second)
          int_set.insert(g);

        for (auto &k : int_set)
          new_string += k;

        int_set.clear();

        current_state.second->next_states.insert(
            make_pair(all_states[new_string], i.first));
        DFA[current_state.first]->next_states.insert(
            make_pair(DFA[new_string], i.first));
      }

      if_letterName_state.clear();
    }

    else {
      // cout << current_state.first << endl;

      for (auto &current_if_letter : all_alphabet) {
        for (auto &iterator_name_state : (current_state.first)) {
          for (auto &next_state :
               all_states[string(1, iterator_name_state)]->next_states) {
            if ((next_state.second == current_if_letter &&
                 p_all_states[next_state.first].size() == 1) &&
                (if_letterName_state[current_if_letter].find(
                     p_all_states[next_state.first]) == string::npos)) {
              if_letterName_state[current_if_letter] +=
                  p_all_states[next_state.first];
              // cout << iterator_name_state << '\t' << current_if_letter <<
              // '\t' << p_all_states[next_state.first] << '\t' <<
              // if_letterName_state[current_if_letter] << endl;
            }
          }
        }

        for (auto &i : if_letterName_state) {
          new_string = "";

          for (auto &g : i.second)
            int_set.insert(g);

          for (auto &k : int_set)
            new_string += k;

          // cout << current_state.first << '\t' << i.first << '\t' <<
          // new_string << '\t' << endl << endl;

          int_set.clear();

          current_state.second->next_states.insert(
              make_pair(all_states[new_string], i.first));

          DFA[current_state.first]->next_states.insert(
              make_pair(DFA[new_string], i.first));
        }

        if_letterName_state.clear();
      }
    }
  }
}

void NFA::delete_empty_states() {
  for (auto &current_state : DFA) {
    for (auto &next_state : current_state.second->next_states) {
      if (current_state.first != p_DFA[next_state.first]) {
        next_state.first->flag = true;
        // cout << '\t' << p_DFA[next_state.first] << endl;
      }
    }
  }

  for (auto &current_state : DFA) {
    if (current_state.second->flag == false) {
      // cout << current_state.first << endl;
      // cout << DFA[current_state.first] << endl;
      delete DFA[current_state.first];
      DFA[current_state.first] = nullptr;
      // DFA.erase(DFA.find(current_state.first));
    }
  }
}

void NFA::set_links(const string &links) {
  string current_state, letter, next_state;

  for (auto iterator_links = links.cbegin(); iterator_links != links.cend();
       ++iterator_links) {
    if (*iterator_links == '(') {
      current_state = "";
      letter = "";
      next_state = "";

      iterator_links++;

      while (*iterator_links != ',') {
        current_state += *iterator_links++;
      }

      iterator_links++;

      while (*iterator_links != ',') {
        letter += *iterator_links++;
      }

      iterator_links++;

      while (*iterator_links != ')') {
        next_state += *iterator_links++;
      }

      this->add_new_link(current_state, letter, next_state);
    }
  }
}

void NFA::get_end_state() {
  for (auto &s : DFA) {
    if (s.second != nullptr && s.second->end_state == true &&
        s.second->flag == true)
      cout << s.first << " ";
  }
}

void NFA::get_start_state() {
  for (auto &s : DFA) {
    if (s.second != nullptr && s.second->start_state == true)
      cout << s.first << " ";
  }
}

void NFA::show_pointers() {
  for (auto &s : DFA) {
    cout << s.first << '\t' << s.second << '\n';
  }

  /*cout << endl;

  for (auto& s : all_states) { cout << s.first << '\t' << s.second << '\n'; }*/
}

void NFA::set_start_state(const string &name_state) {
  DFA[name_state]->start_state = true;
}

void NFA::set_end_state(const string &name_state) {
  DFA[name_state]->end_state = true;
}
