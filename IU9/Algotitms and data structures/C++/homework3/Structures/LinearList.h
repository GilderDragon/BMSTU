#ifndef BMSTU_LINEARLIST_H
#define BMSTU_LINEARLIST_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <stdexcept>


class LinearList {
private:
    // Структура узла списка
    struct ListNode {
        bool isAtom;      // true = атом, false = список
        char atomValue;    // если атом — символ
        std::vector<LinearList> sublist; // если список — вложенные списки
    };

    ListNode data;

public:
    // Конструкторы
    LinearList() {} // пустой список (по умолчанию)

    // Создание атомарного списка
    LinearList(char atom) {
        data.isAtom = true;
        data.atomValue = atom;
    }

    // Создание списка из вектора вложенных списков
    LinearList(const std::vector<LinearList>& lists) {
        data.isAtom = false;
        data.sublist = lists;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return !data.isAtom && data.sublist.empty();
    }

    // Проверка на атомарность
    bool isAtom() const {
        return data.isAtom;
    }

    // Получить атом (если список атомарный)
    char getAtom() const {
        if (data.isAtom) {
            return data.atomValue;
        }
        throw std::runtime_error("Список не атомарный");
    }

    // Получить голову списка
    LinearList head() const {
        if (isEmpty() || isAtom()) {
            throw std::runtime_error("Голова не определена для атомарного или пустого списка");
        }
        return data.sublist.front();
    }

    // Получить хвост списка
    LinearList tail() const {
        if (isEmpty() || isAtom()) {
            throw std::runtime_error("Хвост не определена для атомарного или пустого списка");
        }
        std::vector<LinearList> tailList(data.sublist.begin() + 1, data.sublist.end());
        return LinearList(tailList);
    }

    // Вспомогательный метод для печати
    void print() const {
        if (isAtom()) {
            std::cout << getAtom();
        } else {
            std::cout << "(";
            for (std::size_t i = 0; i < data.sublist.size(); ++i) {
                data.sublist[i].print();
                if (i != data.sublist.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }

    // Рекурсивное вычисление выражения
    double evaluate(const std::map<char, double>& variables) const {
        if (isAtom()) {
            char atom = getAtom();
            if (std::isdigit(atom)) {
                return atom - '0';
            } else if (variables.find(atom) != variables.end()) {
                return variables.at(atom);
            } else if (atom == '+' || atom == '-' || atom == '*' || atom == '/') {
                throw std::runtime_error("Операция не может быть значением");
            } else {
                throw std::runtime_error("Неизвестный атом: " + std::string(1, atom));
            }
        } else {
            // Проверяем, не пустой ли список
            if (isEmpty()) {
                throw std::runtime_error("Пустой список не может быть вычислен");
            }

            LinearList opList = head();
            if (!opList.isAtom()) {
                throw std::runtime_error("Ожидалась операция в голове списка");
            }

            char op = opList.getAtom();

            // Рекурсивно вычисляем аргументы
            std::vector<double> args;
            LinearList rest = tail();
            while (!rest.isEmpty()) {
                args.push_back(rest.head().evaluate(variables));
                rest = rest.tail();
            }

            if (args.size() != 2) {
                throw std::runtime_error("Бинарная операция требует ровно два аргумента");
            }

            double x = args[0];
            double y = args[1];

            switch (op) {
                case '+': return x + y;
                case '-': return x - y;
                case '*': return x * y;
                case '/':
                    if (y == 0) throw std::runtime_error("Деление на ноль");
                    return x / y;
                default:
                    throw std::runtime_error("Неизвестная операция: " + std::string(1, op));
            }
        }
    }
};


#endif //BMSTU_LINEARLIST_H