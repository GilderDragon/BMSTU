#include "Queue.h"
#include <iostream>

using namespace std;


int main() {
    Queue queue;

    queue.add(1);
    queue.add(2);

    cout << queue.is_empty() << endl;
    cout << queue.fisrt() << endl;
    cout << queue.get() << endl;
    cout << queue.get() << endl;
    cout << queue.is_empty() << endl;
}
