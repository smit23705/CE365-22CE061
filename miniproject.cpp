#include <iostream>
#include <string>

using namespace std;

bool chkfor(string s) {
    if (s.find("for") != -1 && s.find("(") != -1 && s.find(")") != -1) {
        return true;
    }
    return false;
}

bool chkwhile(string s) {
    if (s.find("while") != -1 && s.find("(") != -1 && s.find(")") != -1) {
        return true;
    }
    return false;
}

int main() {
    string s;
    cout << "Enter loop: ";
    getline(cin, s);

    if (chkfor(s) || chkwhile(s)) {
        cout << "Valid loop\n";
    } else {
        cout << "Invalid loop\n";
    }

    return 0;
}

