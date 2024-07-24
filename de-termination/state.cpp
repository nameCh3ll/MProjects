#include "state.h"

state::state() {}

state::state(string if_letter, state* link_state) {
  next_states.insert(make_pair(link_state, if_letter));
}

void state::link(state* name_state, string if_letter) {
  /*cout << name_state << '\t' << if_letter << endl;*/

  this->next_states.insert(make_pair(name_state, if_letter));
}
