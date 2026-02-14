#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Функция сортировки вставками для подмассива [left, right)
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i < right; i++) {
        int key = arr[i];
        int j = i - 1;

        // Сравниваем модули чисел
        while (j >= left && abs(arr[j]) > abs(key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Функция слияния двух отсортированных подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;

    // Создаем временные массивы
    vector<int> L(n1), R(n2);

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + i];

    // Слияние временных массивов обратно в arr[left..right)
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (abs(L[i]) <= abs(R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[], если есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Модифицированная рекурсивная функция сортировки слиянием
void modifiedMergeSort(vector<int>& arr, int left, int right) {
    // Если в подмассиве меньше 5 элементов, используем сортировку вставками
    if (right - left < 5) {
        insertionSort(arr, left, right);
        return;
    }

    // Иначе продолжаем рекурсивно делить
    if (left < right - 1) {
        int mid = left + (right - left) / 2;

        // Сортируем левую и правую части
        modifiedMergeSort(arr, left, mid);
        modifiedMergeSort(arr, mid, right);

        // Сливаем отсортированные части
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;

    // Чтение размера массива
    if (!(cin >> n) || n < 0) {
        cerr << "Ошибка: неверный размер массива" << endl;
        return 1;
    }

    vector<int> arr(n);

    // Чтение элементов массива
    for (int i = 0; i < n; i++) {
        if (!(cin >> arr[i])) {
            cerr << "Ошибка: неверный формат данных" << endl;
            return 1;
        }
    }

    // Сортировка модифицированным алгоритмом слияния
    modifiedMergeSort(arr, 0, n);

    // Вывод отсортированного массива
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
