#include "ExpressionEvaluation.h"
#include <iostream>
#include <string>

using namespace std;


int main() {
    string exp = "11 + (2.5 + 34) * 4 ^ (2.5 + 1.5) ^ 0.5";
    ExpressionEvaluation exp1(exp);

    cout << exp1.rpn() << endl;
    cout << exp1.evaluate();
}