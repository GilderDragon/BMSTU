#include <iostream>
#include <vector>

using namespace std;


template<typename T>
void shellsort(int n, T* arr) {

    vector<int> fib = {1, 2};

    while (fib.back() < n) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    for (int k = fib.size() - 1; k > -1; k--) {
        int d = fib[k];
        if (d >= n) continue;

        for (int i = d; i < n; i++) {
            T temp = arr[i];
            int j = i;
            while (j >= d && arr[j - d] > temp) {
                arr[j] = arr[j - d];
                j -= d;
            }
            arr[j] = temp;
        }
    }
}


int main() {
    int arr1[] = {1, 4, 3, 2, 1};
    double arr2[] = {1.2, 3.5, 2.5, 8.5, 3.45};
    string arr3[] = {"banana", "nuts", "apple", "cucumber", "tomato"};

    shellsort(5, arr1);
    shellsort(5, arr2);
    shellsort(5, arr3);

    for (int i : arr1) cout << i << " ";
    cout << "\n";
    for (double i : arr2) cout << i << " ";
    cout << "\n";
    for (string i : arr3) cout << i << " ";
}

