#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <iomanip>
using namespace std;

map<string, vector<vector<string>>> grammar = {
    {"S", {{"A", "B", "C"}, {"D"}}},
    {"A", {{"a"}, {"ε"}}},
    {"B", {{"b"}, {"ε"}}},
    {"C", {{"(", "S", ")"}, {"c"}}},
    {"D", {{"A", "C"}}}
};

vector<string> nonterminals = {"S", "A", "B", "C", "D"};
map<string, set<string>> FIRST = {
    {"S", {"a", "b", "(", "c"}},
    {"A", {"a", "ε"}},
    {"B", {"b", "ε"}},
    {"C", {"(", "c"}},
    {"D", {"a", "("}}
};
map<string, set<string>> FOLLOW = {
    {"S", {")", "$"}},
    {"A", {"b", "(", ")", "$"}},
    {"B", {"c", ")", "$"}},
    {"C", {")", "$"}},
    {"D", {")", "$"}}
};

set<string> terminals = {"a", "b", "(", ")", "c", "$"};
map<string, map<string, vector<string>>> parsing_table;

void construct_parsing_table() {
    for (const auto &nt : nonterminals) {
        for (const auto &production : grammar[nt]) {
            set<string> first_set;
            bool can_produce_epsilon = true;

            for (const string &symbol : production) {
                if (FIRST.find(symbol) != FIRST.end()) {
                    first_set.insert(FIRST[symbol].begin(), FIRST[symbol].end());
                    first_set.erase("ε");
                    if (FIRST[symbol].find("ε") == FIRST[symbol].end()) {
                        can_produce_epsilon = false;
                        break;
                    }
                } else {
                    first_set.insert(symbol);
                    can_produce_epsilon = false;
                    break;
                }
            }
            for (const string &terminal : first_set) {
                parsing_table[nt][terminal] = production;
            }
            if (can_produce_epsilon) {
                for (const string &terminal : FOLLOW[nt]) {
                    parsing_table[nt][terminal] = production;
                }
            }
        }
    }
}

void print_parsing_table() {
    cout << "\nPredictive Parsing Table:\n";
    cout << setw(10) << "";
    for (const string &t : terminals) cout << setw(10) << t;
    cout << "\n";
    for (const string &nt : nonterminals) {
        cout << setw(10) << nt;
        for (const string &t : terminals) {
            if (parsing_table[nt][t].empty())
                cout << setw(10) << "-";
            else {
                string prod = "";
                for (const string &sym : parsing_table[nt][t]) prod += sym + " ";
                cout << setw(10) << prod;
            }
        }
        cout << "\n";
    }
}

bool check_ll1() {
    for (const auto &nt : parsing_table) {
        set<string> seen;
        for (const auto &entry : nt.second) {
            if (!entry.second.empty() && !seen.insert(entry.first).second) {
                return false;
            }
        }
    }
    return true;
}

string parse_string(string input_string) {
    stack<string> parse_stack;
    parse_stack.push("$");
    parse_stack.push("S");
    input_string += "$";
    size_t pointer = 0;

    while (!parse_stack.empty()) {
        string top = parse_stack.top();
        parse_stack.pop();
        string current_symbol(1, input_string[pointer]);

        if (top == current_symbol) {
            pointer++;
            continue;
        } else if (terminals.find(top) != terminals.end() || top == "$") {
            return "Invalid string";
        } else if (parsing_table[top][current_symbol].empty()) {
            return "Invalid string";
        } else {
            vector<string> production = parsing_table[top][current_symbol];
            for (auto it = production.rbegin(); it != production.rend(); ++it) {
                if (*it != "ε") parse_stack.push(*it);
            }
        }
    }
    return (pointer == input_string.size()) ? "Valid string" : "Invalid string";
}

int main() {
    construct_parsing_table();
    print_parsing_table();

    if (check_ll1()) {
        cout << "\nThe given grammar is LL(1).\n";
    } else {
        cout << "\nThe given grammar is NOT LL(1).\n";
    }

    string test_string = "abcabc";
    cout << "\nTesting input: '" << test_string << "'\n";
    cout << parse_string(test_string) << endl;

    return 0;
}
