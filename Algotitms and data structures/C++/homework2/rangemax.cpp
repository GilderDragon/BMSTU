#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Дерево отрезков - хранит максимумы на отрезках
class SegmentTree {
    vector<long long> tree;  // массив для хранения дерева
    int size;                // размер исходного массива

    // Рекурсивное построение дерева
    // node - текущая вершина, l и r - границы отрезка
    void build(vector<long long>& arr, int node, int l, int r) {
        if (l == r) {  // дошли до листа (один элемент)
            tree[node] = arr[l];
            return;
        }
        // Разделяем отрезок пополам
        int m = (l + r) / 2;
        build(arr, node*2, l, m);      // строим левое поддерево
        build(arr, node*2+1, m+1, r);  // строим правое поддерево

        // В текущей вершине храним максимум из детей
        tree[node] = max(tree[node*2], tree[node*2+1]);
    }

    // Обновление одного элемента
    // idx - индекс элемента, val - новое значение
    void update(int node, int l, int r, int idx, long long val) {
        if (l == r) {  // нашли нужный лист
            tree[node] = val;
            return;
        }
        int m = (l + r) / 2;
        // Идем в ту половину, где лежит нужный элемент
        if (idx <= m) update(node*2, l, m, idx, val);
        else update(node*2+1, m+1, r, idx, val);

        // Пересчитываем максимум для текущей вершины
        tree[node] = max(tree[node*2], tree[node*2+1]);
    }

    // Запрос максимума на отрезке [ql, qr]
    long long query(int node, int l, int r, int ql, int qr) {
        // Если текущий отрезок не пересекается с запросом
        if (ql > r || qr < l) return LLONG_MIN;

        // Если текущий отрезок полностью внутри запроса
        if (ql <= l && r <= qr) return tree[node];

        // Иначе разбиваем на две части
        int m = (l + r) / 2;
        long long left_max = query(node*2, l, m, ql, qr);
        long long right_max = query(node*2+1, m+1, r, ql, qr);

        return max(left_max, right_max);
    }

public:
    // Конструктор - строит дерево из массива
    SegmentTree(vector<long long>& arr) {
        size = arr.size();
        tree.resize(4 * size);  // 4*n памяти достаточно
        build(arr, 1, 0, size-1);  // начинаем с корня (вершина 1)
    }

    // Обновить элемент по индексу
    void upd(int idx, long long val) {
        update(1, 0, size-1, idx, val);
    }

    // Найти максимум на отрезке [l, r]
    long long max_range(int l, int r) {
        return query(1, 0, size-1, l, r);
    }
};

int main() {
    // Ускоряем ввод/вывод
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Читаем размер массива
    int n;
    cin >> n;

    // Читаем массив чисел
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Строим дерево отрезков
    SegmentTree tree(arr);

    // Читаем количество операций
    int m;
    cin >> m;

    // Обрабатываем операции
    for (int i = 0; i < m; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "MAX") {
            int l, r;
            cin >> l >> r;
            // Выводим максимум на отрезке
            cout << tree.max_range(l, r) << "\n";
        } else if (cmd == "UPD") {
            int idx;
            long long val;
            cin >> idx >> val;
            // Обновляем элемент
            tree.upd(idx, val);
        }
    }

    return 0;
}
