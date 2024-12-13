/*
Problem Statement : Implement stack as an abstract data type using singly linked list 
and use this ADT for conversion of infix expression to postfix, prefix and evaluation
of postfix and prefix expression.
*/
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(char value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        char value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    char peek() {
        if (isEmpty()) {
            return '\0';
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";
    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        } else {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.isEmpty()) {
        postfix += s.pop();
    }
    return postfix;
}

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        } else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
                case '^': s.push(pow(a, b)); break;
            }
        }
    }
    return s.top();
}

int evaluatePrefix(string prefix) {
    stack<int> s;
    reverse(prefix.begin(), prefix.end());
    for (char ch : prefix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        } else {
            int a = s.top(); s.pop();
            int b = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
                case '^': s.push(pow(a, b)); break;
            }
        }
    }
    return s.top();
}

int main() {
    int choice;
    string expression;

    do {
        cout << "\nMenu:\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Convert Infix to Prefix\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Evaluate Prefix Expression\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter infix expression: ";
                cin >> expression;
                cout << "Postfix: " << infixToPostfix(expression) << endl;
                break;
            case 2:
                cout << "Enter infix expression: ";
                cin >> expression;
                cout << "Prefix: " << infixToPrefix(expression) << endl;
                break;
            case 3:
                cout << "Enter postfix expression: ";
                cin >> expression;
                cout << "Result: " << evaluatePostfix(expression) << endl;
                break;
            case 4:
                cout << "Enter prefix expression: ";
                cin >> expression;
                cout << "Result: " << evaluatePrefix(expression) << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
