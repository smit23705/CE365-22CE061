#include <iostream>
#include <string>
#include <regex>

using namespace std;

class ConstantFoldingOptimizer {
private:
    string expression;

public:
    ConstantFoldingOptimizer(string expr) {
        expression = expr;
    }

    string optimize() {
        return evaluate_constants(expression);
    }

private:
    string evaluate_constants(string expr) {
        regex pattern(R"(\b\d+(\.\d+)?\s*[\+\-\*/]\s*\d+(\.\d+)?\b)");

        while (true) {
            smatch match;
            if (!regex_search(expr, match, pattern)) {
                break;
            }

            string sub_expr = match.str();
            double result = evaluate(sub_expr);
            expr.replace(match.position(), sub_expr.length(), to_string(result));
        }
        return expr;
    }

    double evaluate(string sub_expr) {
        double num1, num2;
        char op;
        sscanf(sub_expr.c_str(), "%lf %c %lf", &num1, &op, &num2);

        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return (num2 != 0) ? num1 / num2 : 0;
            default: return 0;
        }
    }
};

int main() {
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    ConstantFoldingOptimizer optimizer(expr);
    string optimized_expr = optimizer.optimize();

    cout << "Optimized Expression: " << optimized_expr << endl;
    return 0;
}
