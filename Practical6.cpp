#include <iostream>
#include <string>
using namespace std;

class RecursiveDescentParser {
private:
    string input;
    size_t index;

public:
    RecursiveDescentParser(string input_string) {
        input = "";
        for (char c : input_string) {
            if (c != ' ') input += c;
        }
        index = 0;
    }

    void parse() {
        if (S() && index == input.length()) {
            cout << "Valid string" << endl;
        } else {
            cout << "Invalid string" << endl;
        }
    }

private:
    bool S() {
        if (match('a')) {
            return true;
        } else if (match('(')) {
            if (L() && match(')')) {
                return true;
            }
        }
        return false;
    }

    bool L() {
        if (S()) {
            return L_prime();
        }
        return false;
    }

    bool L_prime() {
        if (match(',')) {
            if (S()) {
                return L_prime();
            }
            return false;
        }
        return true;
    }

    bool match(char c) {
        if (index < input.length() && input[index] == c) {
            index++;
            return true;
        }
        return false;
    }
};

int main() {
    string user_input;
    cout << "Enter a string to validate: ";
    getline(cin, user_input);
    RecursiveDescentParser parser(user_input);
    parser.parse();
    return 0;
}
