#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <regex>

using namespace std;

string removeComments(const string &src) {
    string result = regex_replace(src, regex("//.*"), "");
    return regex_replace(result, regex("/\\*.*?\\*/"), "", regex_constants::dotall);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: ./lexical_analyzer <source_file.c>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "File '" << argv[1] << "' not found." << endl;
        return 1;
    }

    string src((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    src = removeComments(src);

    unordered_set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
                                      "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
                                      "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                                      "union", "unsigned", "void", "volatile", "while"};

    unordered_set<string> type_keywords = {"int", "char", "float", "double", "void", "long", "short", "signed", "unsigned"};
    unordered_set<string> op_multi = {"==", "!=", "<=", ">=", "++", "--", "&&", "||"};
    unordered_set<char> op_single = {'+', '-', '*', '/', '=', '<', '>'};
    unordered_set<char> punctuation_set = {'(', ')', '{', '}', '[', ']', ',', ';'};

    vector<tuple<string, string, int>> tokens;
    vector<tuple<string, int>> errors;
    unordered_set<string> symbol_table;

    int line_no = 1, pos = 0, length = src.length();

    while (pos < length) {
        char ch = src[pos];
        if (isspace(ch)) {
            if (ch == '\n') line_no++;
            pos++;
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            int start = pos;
            while (pos < length && (isalnum(src[pos]) || src[pos] == '_')) pos++;
            string lexeme = src.substr(start, pos - start);
            if (keywords.count(lexeme))
                tokens.emplace_back("Keyword", lexeme, line_no);
            else {
                tokens.emplace_back("Identifier", lexeme, line_no);
                symbol_table.insert(lexeme);
            }
            continue;
        }

        if (isdigit(ch)) {
            int start = pos;
            while (pos < length && isdigit(src[pos])) pos++;
            string lexeme = src.substr(start, pos - start);
            tokens.emplace_back("Constant", lexeme, line_no);
            continue;
        }

        if (ch == '"' || ch == '\'') {
            char quote = ch;
            string literal(1, ch);
            pos++;
            while (pos < length) {
                char c = src[pos];
                literal += c;
                if (c == '\\' && pos + 1 < length) literal += src[++pos];
                else if (c == quote) { pos++; break; }
                pos++;
            }
            tokens.emplace_back("String", literal, line_no);
            continue;
        }

        if (pos + 1 < length && op_multi.count(src.substr(pos, 2))) {
            tokens.emplace_back("Operator", src.substr(pos, 2), line_no);
            pos += 2;
            continue;
        }
        if (op_single.count(ch)) {
            tokens.emplace_back("Operator", string(1, ch), line_no);
            pos++;
            continue;
        }
        if (punctuation_set.count(ch)) {
            tokens.emplace_back("Punctuation", string(1, ch), line_no);
            pos++;
            continue;
        }

        errors.emplace_back(string(1, ch), line_no);
        pos++;
    }

    cout << "TOKENS" << endl;
    for (const auto &[type, lexeme, lno] : tokens) {
        cout << type << ": " << lexeme << " (Line " << lno << ")" << endl;
    }

    cout << "\nLEXICAL ERRORS" << endl;
    if (errors.empty()) cout << "None" << endl;
    else for (const auto &[lex, lno] : errors) {
        cout << lex << " invalid lexeme at line " << lno << endl;
    }

    cout << "\nSYMBOL TABLE ENTRIES" << endl;
    int idx = 1;
    for (const auto &ident : symbol_table) {
        cout << idx++ << ") " << ident << endl;
    }

    return 0;
}
