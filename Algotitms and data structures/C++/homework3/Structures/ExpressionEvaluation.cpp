#include "ExpressionEvaluation.h"
#include <iostream>
#include <string>

using namespace std;


int main() {
    string exp1 = "11 + (2.5 + 34) * 4 ^ (2.5 + 1.5) ^ (1 - 0.5)";
    ExpressionEvaluation expression(exp1);

    cout << expression.rpn() << endl;
    cout << expression.evaluate();
}