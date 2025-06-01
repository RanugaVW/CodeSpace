#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

// Precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    if (op == '%' || op == '@') return 3;
    return 0;
}

// Associativity: true = left to right, false = right to left
bool isLeftAssoc(char op) {
    return (op == '+' || op == '-' || op == '*');
}

// Apply custom binary operation
int applyOp(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return abs(a - b);
        case '*': return a * b;
        case '%': return min(a, b);
        case '@': return max(a, b);
    }
    return 0;
}

// Check if character is a valid operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '%' || c == '@';
}

// Check if token is a valid number (no leading zero unless 0)
bool isValidNumber(const string& token) {
    if (token.empty()) return false;
    if (token.length() > 1 && token[0] == '0') return false;
    return all_of(token.begin(), token.end(), ::isdigit);
}

// Parse and evaluate expression
bool evaluateExpression(const string& exprRaw, int& result) {
    string expr;
    for (char c : exprRaw) {
        if (c != ' ') expr += c;
    }

    if (expr.empty()) return false;

    vector<string> output;
    stack<char> ops;
    string num = "";

    char prev = '\0';
    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (isdigit(c)) {
            num += c;
            prev = c;
        } else {
            if (!num.empty()) {
                if (!isValidNumber(num)) return false;
                output.push_back(num);
                num.clear();
            }

            if (c == '(') {
                // Invalid: digit before '(' like 3(2)
                if (isdigit(prev) || prev == ')') return false;
                ops.push(c);
                prev = c;
            } else if (c == ')') {
                if (isOperator(prev) || prev == '(') return false;
                while (!ops.empty() && ops.top() != '(') {
                    output.push_back(string(1, ops.top()));
                    ops.pop();
                }
                if (ops.empty() || ops.top() != '(') return false;
                ops.pop();
                prev = c;
            } else if (isOperator(c)) {
                // Invalid cases: operator after operator or at start
                if (prev == '\0' || isOperator(prev) || prev == '(') return false;

                while (!ops.empty() && isOperator(ops.top())) {
                    char top = ops.top();
                    if ((isLeftAssoc(c) && precedence(c) <= precedence(top)) ||
                        (!isLeftAssoc(c) && precedence(c) < precedence(top))) {
                        output.push_back(string(1, top));
                        ops.pop();
                    } else break;
                }
                ops.push(c);
                prev = c;
            } else {
                return false; // Invalid character
            }
        }
    }

    if (!num.empty()) {
        if (!isValidNumber(num)) return false;
        output.push_back(num);
    }

    if (isOperator(prev) || prev == '(') return false;

    while (!ops.empty()) {
        if (ops.top() == '(' || ops.top() == ')') return false;
        output.push_back(string(1, ops.top()));
        ops.pop();
    }

    // Evaluate postfix expression
    stack<int> eval;
    for (const string& token : output) {
        if (isdigit(token[0])) {
            eval.push(stoi(token));
        } else if (token.length() == 1 && isOperator(token[0])) {
            if (eval.size() < 2) return false;
            int b = eval.top(); eval.pop();
            int a = eval.top(); eval.pop();
            eval.push(applyOp(token[0], a, b));
        } else {
            return false;
        }
    }

    if (eval.size() != 1) return false;
    result = eval.top();
    return true;
}

// Main function
int main() {
    int N;
    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; ++i) {
        string expr;
        getline(cin, expr);
        int val = 0;
        if (evaluateExpression(expr, val)) {
            cout << val << endl;
        } else {
            cout << "invalid" << endl;
        }
    }

    return 0;
}
