#include "List.h"
#include <iostream>

using namespace std;


int main() {
    List<int> list;

    list.append(6);
    list.append(5);
    list.append(4);

    cout << list.get(0) << endl;
    cout << list[0] << endl;
    cout << list.pop() << endl;
    cout << list.size() << endl;
    cout << list.pop(-1) << endl;
}
