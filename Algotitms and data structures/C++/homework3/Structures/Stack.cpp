#include "Stack.h"
#include <iostream>

using namespace std;


int main() {
    Stack<int> stack;
    stack.push(4);
    stack.push(7);
    cout << stack.isEmpty() << endl;
    cout << stack.front() << endl;
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    cout << stack.isEmpty();
}
