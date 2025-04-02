#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

map<string, vector<vector<string>>> grammar = {
    {"S", {{"A", "B", "C"}, {"D"}}},
    {"A", {{"a"}, {"ε"}}},
    {"B", {{"b"}, {"ε"}}},
    {"C", {{"(", "S", ")"}, {"c"}}},
    {"D", {{"A", "C"}}}
};

vector<string> nonterminals = {"S", "A", "B", "C", "D"};
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;

bool is_nonterminal(const string &symbol) {
    return grammar.find(symbol) != grammar.end();
}

void compute_first_sets() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (const string &nt : nonterminals) {
            for (const auto &production : grammar[nt]) {
                bool can_produce_epsilon = true;
                for (const string &symbol : production) {
                    if (!is_nonterminal(symbol)) {
                        auto before_size = FIRST[nt].size();
                        FIRST[nt].insert(symbol);
                        if (FIRST[nt].size() > before_size) changed = true;
                        can_produce_epsilon = false;
                        break;
                    } else {
                        auto before_size = FIRST[nt].size();
                        FIRST[nt].insert(FIRST[symbol].begin(), FIRST[symbol].end());
                        FIRST[nt].erase("ε");
                        if (FIRST[nt].size() > before_size) changed = true;
                        if (FIRST[symbol].find("ε") == FIRST[symbol].end()) {
                            can_produce_epsilon = false;
                            break;
                        }
                    }
                }
                if (can_produce_epsilon) {
                    auto before_size = FIRST[nt].size();
                    FIRST[nt].insert("ε");
                    if (FIRST[nt].size() > before_size) changed = true;
                }
            }
        }
    }
}

void compute_follow_sets() {
    FOLLOW["S"].insert("$");
    bool changed = true;
    while (changed) {
        changed = false;
        for (const string &nt : nonterminals) {
            for (const auto &production : grammar[nt]) {
                int length = production.size();
                for (int i = 0; i < length; i++) {
                    if (is_nonterminal(production[i])) {
                        auto before_size = FOLLOW[production[i]].size();
                        if (i + 1 < length) {
                            set<string> first_beta;
                            bool can_all_epsilon = true;
                            for (int j = i + 1; j < length; j++) {
                                if (!is_nonterminal(production[j])) {
                                    first_beta.insert(production[j]);
                                    can_all_epsilon = false;
                                    break;
                                } else {
                                    first_beta.insert(FIRST[production[j]].begin(), FIRST[production[j]].end());
                                    first_beta.erase("ε");
                                    if (FIRST[production[j]].find("ε") == FIRST[production[j]].end()) {
                                        can_all_epsilon = false;
                                        break;
                                    }
                                }
                            }
                            FOLLOW[production[i]].insert(first_beta.begin(), first_beta.end());
                            if (can_all_epsilon) {
                                FOLLOW[production[i]].insert(FOLLOW[nt].begin(), FOLLOW[nt].end());
                            }
                        } else {
                            FOLLOW[production[i]].insert(FOLLOW[nt].begin(), FOLLOW[nt].end());
                        }
                        if (FOLLOW[production[i]].size() > before_size) changed = true;
                    }
                }
            }
        }
    }
}

void print_sets() {
    cout << "\nFirst Sets:" << endl;
    for (const string &nt : nonterminals) {
        cout << "FIRST(" << nt << ") = {";
        bool first = true;
        for (const string &symbol : FIRST[nt]) {
            if (!first) cout << ", ";
            cout << symbol;
            first = false;
        }
        cout << "}" << endl;
    }

    cout << "\nFollow Sets:" << endl;
    for (const string &nt : nonterminals) {
        cout << "FOLLOW(" << nt << ") = {";
        bool first = true;
        for (const string &symbol : FOLLOW[nt]) {
            if (!first) cout << ", ";
            cout << symbol;
            first = false;
        }
        cout << "}" << endl;
    }
}

int main() {
    compute_first_sets();
    compute_follow_sets();
    print_sets();
    return 0;
}
