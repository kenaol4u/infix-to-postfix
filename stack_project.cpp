#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string infix) {
    string postfix = "";
    stack<char> st;

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix += ch;
        }
        else if (isOperator(ch)) {
            while (!st.empty() && getPrecedence(ch) <= getPrecedence(st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Function to evaluate postfix expression
double evaluatePostfix(string postfix) {
    stack<double> st;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            st.push(ch - '0');
        }
        else if (isOperator(ch)) {
            double operand2 = st.top();
            st.pop();
            double operand1 = st.top();
            st.pop();
            double result;

            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
            }

            st.push(result);
        }
    }

    return st.top();
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    double result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}

