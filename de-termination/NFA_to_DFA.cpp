#include "NFA.h"

int main() {
  string name_state = "";
  string name_alphabet = "";
  string final_state = "";
  string start_state = "";
  string links = "";

  cout << "Enter set of states: ";
  getline(cin, name_state);
  cout << endl;
  cout << "Enter the input alphabet: ";
  getline(cin, name_alphabet);
  cout << endl;
  cout << "Enter a set of initial states: ";
  getline(cin, start_state);
  cout << endl;
  cout << "Enter a set of final states: ";
  getline(cin, final_state);
  cout << endl;

  cout << "Enter links: ";
  getline(cin, links);
  cout << endl;

  NFA nfa(name_alphabet, name_state, start_state, final_state);
  nfa.set_links(links);
  nfa.create_DFA();
  nfa.delete_empty_states();
  nfa.show_all_states();
  cout << endl;

  cout << "Initial states: ";
  nfa.get_end_state();
  cout << endl;
  cout << "Final states: ";
  nfa.get_start_state();
  cout << endl;
  //(1,a,1) (1,a,4) (4,a,4) (4,b,3) (4,b,5) (5,a,3)
}
