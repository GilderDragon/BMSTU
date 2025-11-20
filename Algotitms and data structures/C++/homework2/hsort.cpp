#include <iostream>

using namespace std;


template<typename T>
void heapyfy(T* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;

    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapyfy(arr, n, largest);
    }
}


template<typename T>
void hsort(T* arr, int n) {
    for (int i = n / 2 - 1; i > -1; i--) heapyfy(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);

        heapyfy(arr, i, 0);
    }
}


int count_a(string* str) {
    int cnt = 0;
    for (char i : *str) {
        if (i == 'a') cnt++;
    }
    return cnt;
}


int main() {
    int arr1[] = {5, 3, 1, 6, 4};

    hsort(arr1, 5);

    for (int i : arr1) cout << i << " ";
    cout << endl;


    string arr2[] = {"banana", "apple", "avocado", "grape", "ananas"};

    int arr3[5];
    string arr4[5];

    for (int i = 0; i < 5; i++) arr3[i] = count_a(&arr2[i]);

    hsort(arr3, 5);

    for (string word : arr2) {
        for (int i = 0; i < 5; i++) {
            if (count_a(&word) == arr3[i] && arr4[i].empty()) {
                arr4[i] = word;
                break;
            }
        }
    }

    for (int i : arr3) cout << i << " ";
    cout << endl;

    for (string i : arr4) cout << i << " ";
}
