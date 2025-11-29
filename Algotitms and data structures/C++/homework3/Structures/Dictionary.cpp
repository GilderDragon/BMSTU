#include <iostream>
#include "Dictionary.h"

using namespace std;


int main() {
    Dict<string, list<int>> dict;

    dict["alla"] = {4, 2, 5};
    dict["denis"] = {3, 4, 4};
    dict["sasha"] = {5, 5, 5};

    for (int i : dict["denis"]) cout << i << " ";
    cout << endl;
    for (string i : dict.keys()) cout << i << " ";
    cout << endl;
    cout << dict.isEmpty();
    cout << endl;
    cout << dict.size();
    cout << endl;

    dict.remove("alla");

    cout << dict.size();
    cout << endl;
    for (string i : dict.keys()) cout << i << " ";
    cout << endl;

    dict.insert("oleg", {4, 4, 5});

    for (string i : dict.keys()) cout << i << " ";
}