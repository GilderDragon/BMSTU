#include "Queue.h"
#include <iostream>

using namespace std;


int main() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);

    cout << queue.isEmpty() << endl;
    cout << queue.front() << endl;
    cout << queue.dequeue() << endl;
    cout << queue.dequeue() << endl;
    cout << queue.isEmpty() << endl;
}
