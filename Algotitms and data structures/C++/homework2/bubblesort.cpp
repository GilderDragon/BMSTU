#include <iostream>

using namespace std;


template<typename T>
void bubblesort(int n, T* arr) {
    T temp;
    int flag = -1, start, stop;
    bool swapped;

    for (int i = 0; i < n; i++) {

        flag *= -1;

        if (flag >  0) {
            start = 0;
            stop = n - 1;
        } else {
            start = n - 2;
            stop = 1;
        }

        swapped = true;

        for (int j = start; flag * j < stop; j += flag) {
            if (arr[j] > arr[j + 1]) {
                swapped = false;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        if (swapped) break;
    }
}


int main() {
    int arr1[] = {1, 4, 3, 2, 1};
    double arr2[] = {1.2, 3.5, 2.5, 8.5, 3.45};
    string arr3[] = {"banana", "nuts", "apple", "cucumber", "tomato"};

    bubblesort(5, arr1);
    bubblesort(5, arr2);
    bubblesort(5, arr3);

    for (int i : arr1) cout << i << " ";
    cout << "\n";
    for (double i : arr2) cout << i << " ";
    cout << "\n";
    for (string i : arr3) cout << i << " ";
}
