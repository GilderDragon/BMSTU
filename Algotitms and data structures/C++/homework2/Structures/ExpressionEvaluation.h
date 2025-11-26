#ifndef BMSTU_EXPRESSIONEVALUATION_H
#define BMSTU_EXPRESSIONEVALUATION_H
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <map>
#include <stdexcept>


class ExpressionEvaluation {
private:
    std::string originalExpression;
    std::string RPNExpression;
    std::string digits = "1234567890.";
    std::string operators = "+-*/^";
    std::map<std::string, int> priority = {
        {"+", 1}, {"-", 1},
        {"*", 2}, {"/", 2},
        {"^", 3}
    };

    [[nodiscard]] bool isDigit(const char& c) const {
        return std::any_of(digits.begin(), digits.end(), [c](char i){return c == i;});
    }

    [[nodiscard]] bool isOperator(const char& c) const {
        return std::any_of(operators.begin(), operators.end(), [c](char i){return c == i;});
    }

    std::string convertToRPN(const std::string& expression) {
        std::string result;
        std::stack<std::string> ops;

        for (int i = 0; i < expression.size(); i++) {
            const char c = expression[i];
            
            if (isDigit(c)) {
                if (i + 1 < expression.size() && isDigit(expression[i+1])) {
                    result += std::string(1, c);
                } else {
                    result += std::string(1, c) + " ";
                }
            } else if (isOperator(c)) {
                while (!ops.empty() && priority[ops.top()] >= priority[std::string(1, c)]) {
                    result += ops.top() + " ";
                    ops.pop();
                }
                ops.emplace(1, c);
            } else if (c == '(') {
                ops.emplace(1, c);
            } else if (c == ')') {
                while (ops.top() != "(") {
                    result += ops.top() + " ";
                    ops.pop();
                }
                ops.pop();
            }
        }
        while (!ops.empty()) {
            result += ops.top() + " ";
            ops.pop();
        }

        if (result.back() == ' ') {
            result.pop_back();
        }

        return result;
    }
public:
    explicit ExpressionEvaluation(const std::string& expression) : originalExpression(expression) {
        RPNExpression = convertToRPN(expression);
    }

    const std::string& original() {
        return originalExpression;
    }

    const std::string& rpn() {
        return RPNExpression;
    }

    [[nodiscard]] double evaluate() const {
        std::stack<double> st;
        std::string temp;

        for (int i = 0; i < RPNExpression.size(); i++) {
            char c = RPNExpression[i];
            if (isDigit(c)) {
                if (i + 1 < RPNExpression.size() && isDigit(RPNExpression[i + 1])) {
                    temp += std::string(1, c);
                } else {
                    st.push(std::stod(temp + std::string(1, c)));
                    temp.clear();
                }
            } else if (isOperator(c)) {
                double number;
                double number2 = st.top();
                st.pop();
                double number1 = st.top();
                st.pop();
                switch (c){
                    case '+':
                        number = number1 + number2;
                        break;
                    case '-':
                        number = number1 - number2;
                        break;
                    case '*':
                        number = number1 * number2;
                        break;
                    case '/':
                        number = number1 / number2;
                        break;
                    case '^':
                        number = std::pow(number1, number2);
                        break;
                    default:
                        throw std::runtime_error("Stupid programmer");
                }
                st.push(number);
            }
        }
        return st.top();
    }
};


#endif //BMSTU_EXPRESSIONEVALUATION_H