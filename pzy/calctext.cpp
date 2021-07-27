#include <iostream>
#include<stack>
#include<string>
using namespace std;
stack<double>num;
stack<char>op;
void calcOnce() {
    if (num.size() <= 1) {
        return;
    }
    double ans,a,b;
    b = num.top();
    num.pop();
    a = num.top();
    num.pop();
    switch (op.top()) {
    case '+':
        ans = a + b;
        break;
    case '-':
        ans = a - b;
        break;
    case '*':
        ans = a * b;
        break;

    default:
        ans = a / b;
    }
    op.pop();
    num.push(ans);
}

bool juidgePrior(char s) {
    if (!op.empty()) {
        if (op.top() == '*' || op.top() == '/'|| s == '+' || s == '-') {
            return true;
        }
    }
    return false;
}

double calculateText(string s) {
    int cutIndex = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            num.push(stoi(s.substr(cutIndex, i)));
            cutIndex = i + 1;
            while (juidgePrior(s[i])) {
                calcOnce();
            }
            op.push(s[i]);
        }
    }
    num.push(stoi(s.substr(cutIndex, s.length())));
    calcOnce();
    return num.top();
}
