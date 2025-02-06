#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
using namespace std;

using TransitionTable = map<pair<int, char>, int>;

bool validateString(const string& input, int initialState, const set<int>& acceptingStates, const TransitionTable& transitions) {
    int currentState = initialState;

    for (char symbol : input) {
        if (transitions.find({currentState, symbol}) != transitions.end()) {
            currentState = transitions.at({currentState, symbol});
        } else {
            return false;
        }
    }

    return acceptingStates.find(currentState) != acceptingStates.end();
}

int main() {
    int numSymbols, numStates, initialState, numAcceptingStates;
    vector<char> symbols;
    set<int> acceptingStates;
    TransitionTable transitions;

    cout << "Number of input symbols: ";
    cin >> numSymbols;
    symbols.resize(numSymbols);

    cout << "Input symbols: ";
    for (int i = 0; i < numSymbols; ++i) {
        cin >> symbols[i];
    }

    cout << "Enter number of states: ";
    cin >> numStates;

    cout << "Initial state: ";
    cin >> initialState;

    cout << "Number of accepting states: ";
    cin >> numAcceptingStates;

    cout << "Accepting states: ";
    for (int i = 0; i < numAcceptingStates; ++i) {
        int state;
        cin >> state;
        acceptingStates.insert(state);
    }

    cout << "Transition table (format: state input_symbol next_state):\n";
    for (int i = 0; i < numStates * numSymbols; ++i) {
        int currentState, nextState;
        char symbol;
        cin >> currentState >> symbol >> nextState;
        transitions[{currentState, symbol}] = nextState;
    }

    string inputString;
    cout << "Input string: ";
    cin >> inputString;

    if (validateString(inputString, initialState, acceptingStates, transitions)) {
        cout << "Valid string\n";
    } else {
        cout << "Invalid string\n";
    }

    return 0;
}
