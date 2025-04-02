#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <sstream>

using namespace std;

class QuadrupleGenerator {
private:
    int temp_count;
    vector<tuple<string, string, string, string>> quadruples;
    unordered_map<char, int> precedence;

public:
    QuadrupleGenerator() {
        temp_count = 1;
        precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    }

    string new_temp() {
        return "t" + to_string(temp_count++);
    }

    vector<string> tokenize(string expression) {
        vector<string> tokens;
        stringstream ss(expression);
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<string> infix_to_postfix(vector<string> tokens) {
        vector<string> output;
        stack<char> operators;

        for (string token : tokens) {
            if (isdigit(token[0])) {
                output.push_back(token);
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                while (!operators.empty() && precedence[operators.top()] >= precedence[token[0]]) {
                    output.push_back(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(token[0]);
            } else if (token == "(") {
                operators.push('(');
            } else if (token == ")") {
                while (!operators.empty() && operators.top() != '(') {
                    output.push_back(string(1, operators.top()));
                    operators.pop();
                }
                operators.pop();
            }
        }

        while (!operators.empty()) {
            output.push_back(string(1, operators.top()));
            operators.pop();
        }

        return output;
    }

    void evaluate_postfix(vector<string> postfix) {
        stack<string> stack;
        for (string token : postfix) {
            if (isdigit(token[0])) {
                stack.push(token);
            } else {
                string op2 = stack.top(); stack.pop();
                string op1 = stack.top(); stack.pop();
                string temp_var = new_temp();
                quadruples.push_back({token, op1, op2, temp_var});
                stack.push(temp_var);
            }
        }
    }

    void generate_quadruples(string expression) {
        vector<string> tokens = tokenize(expression);
        vector<string> postfix = infix_to_postfix(tokens);
        evaluate_postfix(postfix);
    }

    void display_quadruples() {
        cout << "\nQuadruples Generated:\n";
        cout << "Operator   Operand 1   Operand 2   Result\n";
        for (auto &quad : quadruples) {
            cout << get<0>(quad) << "        " << get<1>(quad) << "          "
                 << get<2>(quad) << "          " << get<3>(quad) << "\n";
        }
    }
};

int main() {
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    QuadrupleGenerator generator;
    generator.generate_quadruples(expr);
    generator.display_quadruples();

    return 0;
}
