#include "Stack.h"
#include <iostream>

using namespace std;


int main() {
    Stack stack;
    stack.add(4);
    stack.add(7);
    cout << stack.is_empty() << endl;
    cout << stack.top() << endl;
    cout << stack.get() << endl;
    cout << stack.get() << endl;
    cout << stack.is_empty();
}
