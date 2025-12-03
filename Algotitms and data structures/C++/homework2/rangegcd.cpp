#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Дерево отрезков для вычисления НОД
class SegmentTree {
    vector<int> tree;  // массив для хранения дерева
    int size;          // размер исходного массива

    // Функция вычисления НОД двух чисел
    int gcd(int a, int b) {
        // Берем абсолютные значения (НОД от модулей)
        a = abs(a);
        b = abs(b);

        // Алгоритм Евклида
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // Рекурсивное построение дерева
    // node - индекс текущей вершины
    // l, r - границы отрезка в исходном массиве
    void build(vector<int>& arr, int node, int l, int r) {
        // Базовый случай: лист дерева (один элемент)
        if (l == r) {
            tree[node] = arr[l];
            return;
        }

        // Разделяем отрезок пополам
        int mid = (l + r) / 2;

        // Строим левое поддерево
        build(arr, node * 2, l, mid);

        // Строим правое поддерево
        build(arr, node * 2 + 1, mid + 1, r);

        // В текущей вершине храним НОД значений детей
        tree[node] = gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    // Рекурсивный запрос НОД на отрезке [ql, qr]
    int query(int node, int l, int r, int ql, int qr) {
        // Если текущий отрезок не пересекается с запросом
        if (ql > r || qr < l) {
            return 0;  // НОД(x, 0) = x, поэтому 0 - нейтральный элемент
        }

        // Если текущий отрезок полностью внутри запроса
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        // Иначе разбиваем на две части
        int mid = (l + r) / 2;

        // НОД левой части отрезка
        int left_gcd = query(node * 2, l, mid, ql, qr);

        // НОД правой части отрезка
        int right_gcd = query(node * 2 + 1, mid + 1, r, ql, qr);

        // Возвращаем НОД от двух частей
        return gcd(left_gcd, right_gcd);
    }

public:
    // Конструктор: строит дерево из массива
    SegmentTree(vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size);  // 4n памяти достаточно
        build(arr, 1, 0, size - 1);  // начинаем с корня (вершина 1)
    }

    // Публичный метод для запроса НОД на отрезке [l, r]
    int get_gcd(int l, int r) {
        return query(1, 0, size - 1, l, r);
    }
};

int main() {
    // Ускоряем ввод/вывод
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Чтение размера массива
    int n;
    cin >> n;

    // Чтение массива чисел
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Построение дерева отрезков
    SegmentTree tree(arr);

    // Чтение количества запросов
    int m;
    cin >> m;

    // Обработка запросов
    while (m--) {
        int l, r;
        cin >> l >> r;

        // Вывод НОД на отрезке [l, r]
        cout << tree.get_gcd(l, r) << "\n";
    }

    return 0;
}
