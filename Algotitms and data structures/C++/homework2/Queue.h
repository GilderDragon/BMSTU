#ifndef BMSTU_QUEUE_H
#define BMSTU_QUEUE_H
#include <vector>

using namespace std;


template<typename T>
class Queue {
private:
    vector<T> queue;

public:
    void add(T n) {
        queue.push_back(n);
    }

    T get() {
        T value = queue[0];
        queue.erase(queue.begin());
        return value;
    }

    T fisrt() {
        return queue[0];
    }

    bool is_empty() {
        return queue.empty();
    }
};


#endif //BMSTU_QUEUE_H