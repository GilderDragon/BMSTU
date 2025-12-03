#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Функция сортировки прямым выбором (selection sort)
void selectionSort(vector<int>& arr, int left, int right) {
    for (int i = left; i < right - 1; i++) {
        int minIndex = i;
        // Находим минимальный элемент в оставшейся части
        for (int j = i + 1; j < right; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Меняем местами с текущим элементом
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Функция разделения (partition) для быстрой сортировки
// Возвращает индекс опорного элемента после разделения
int partition(vector<int>& arr, int left, int right) {
    // Выбираем опорный элемент (медиана трех)
    int mid = left + (right - left) / 2;

    // Сортируем left, mid, right для выбора медианы
    if (arr[right - 1] < arr[left])
        swap(arr[left], arr[right - 1]);
    if (arr[mid] < arr[left])
        swap(arr[left], arr[mid]);
    if (arr[right - 1] < arr[mid])
        swap(arr[mid], arr[right - 1]);

    // Опорный элемент - медиана (arr[mid])
    int pivot = arr[mid];

    // Меняем медиану с предпоследним элементом
    swap(arr[mid], arr[right - 2]);

    // Разделение массива
    int i = left;
    int j = right - 2;

    while (true) {
        // Ищем элемент >= опорному слева
        while (arr[++i] < pivot) {}

        // Ищем элемент <= опорному справа
        while (pivot < arr[--j]) {}

        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            break;
        }
    }

    // Возвращаем опорный элемент на правильную позицию
    swap(arr[i], arr[right - 2]);

    return i;
}

// Итеративная версия быстрой сортировки с ограниченной глубиной стека
void iterativeQuickSort(vector<int>& arr, int n, int m) {
    // Используем стек для хранения границ подмассивов
    stack<pair<int, int>> stk;
    stk.push({0, n});

    while (!stk.empty()) {
        int left = stk.top().first;
        int right = stk.top().second;
        stk.pop();

        int size = right - left;

        // Если подмассив меньше m, используем сортировку прямым выбором
        if (size < m) {
            selectionSort(arr, left, right);
            continue;
        }

        // Разделяем подмассив
        int pivotIndex = partition(arr, left, right);

        // Определяем размеры левой и правой частей
        int leftSize = pivotIndex - left;
        int rightSize = right - (pivotIndex + 1);

        // Чтобы ограничить глубину стека O(log n), сначала обрабатываем
        // меньшую часть рекурсивно, а большую часть оставляем в стеке
        // Это гарантирует, что стек будет содержать не более O(log n) элементов

        // Определяем меньшую и большую части
        pair<int, int> smaller, larger;
        if (leftSize < rightSize) {
            smaller = {left, pivotIndex};
            larger = {pivotIndex + 1, right};
        } else {
            smaller = {pivotIndex + 1, right};
            larger = {left, pivotIndex};
        }

        // Сначала обрабатываем меньшую часть (добавляем в стек)
        stk.push(larger);  // Сначала обрабатываем большую часть
        stk.push(smaller); // Затем меньшую (будет обработана первой)

        // Удаляем из стека, если обе части очень маленькие
        if (larger.second - larger.first < m) {
            stk.pop();
            selectionSort(arr, larger.first, larger.second);
        }
    }
}

int main() {
    int n, m;

    // Чтение размера массива и порога m
    if (!(cin >> n >> m) || n < 0 || m < 0) {
        cerr << "Ошибка: неверные входные данные" << endl;
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

    // Если массив пустой или из одного элемента
    if (n <= 1) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return 0;
    }

    // Запуск итеративной быстрой сортировки
    iterativeQuickSort(arr, n, m);

    // Вывод отсортированного массива
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
