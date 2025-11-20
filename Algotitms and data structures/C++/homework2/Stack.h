#ifndef BMSTU_STACK_H
#define BMSTU_STACK_H
#include <vector>

using namespace std;


template<typename T>
class Stack {
private:
    vector<T> stack;

public:
    void add(T n) {
        stack.push_back(n);
    }

    T get() {
        T value = stack.back();
        stack.pop_back();
        return value;
    }

    T top() {
        return stack.back();
    }

    bool is_empty() {
        return stack.empty();
    }
};


#endif //BMSTU_STACK_H