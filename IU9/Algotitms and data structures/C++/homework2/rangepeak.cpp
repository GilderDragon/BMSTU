#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;  // количество пиков на отрезке
    vector<int> arr;   // копия массива
    int size;

    // Проверяет, является ли элемент i пиком
    bool is_peak(int i) {
        if (i <= 0 || i >= size-1) return false;  // граничные элементы
        return arr[i] >= arr[i-1] && arr[i] >= arr[i+1];
    }

    // Пересчет пиков при изменении
    void recalc(int i) {
        // Пик может быть на позициях i-1, i, i+1
        int new_peak = 0;
        for (int pos = max(1, i-1); pos <= min(size-2, i+1); pos++) {
            if (arr[pos] >= arr[pos-1] && arr[pos] >= arr[pos+1]) {
                new_peak++;
            }
        }

        // Обновляем дерево
        update_tree(1, 0, size-1, max(1, i-1), min(size-2, i+1), new_peak);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = (l > 0 && l < size-1 && is_peak(l)) ? 1 : 0;
            return;
        }
        int m = (l + r) / 2;
        build(node*2, l, m);
        build(node*2+1, m+1, r);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void update_tree(int node, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node] = val;
            return;
        }
        int m = (l + r) / 2;
        update_tree(node*2, l, m, ql, qr, val);
        update_tree(node*2+1, m+1, r, ql, qr, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        return query(node*2, l, m, ql, qr) +
               query(node*2+1, m+1, r, ql, qr);
    }

public:
    SegmentTree(vector<int>& nums) {
        size = nums.size();
        arr = nums;
        tree.resize(4 * size);
        build(1, 0, size-1);
    }

    void upd(int idx, int val) {
        arr[idx] = val;
        recalc(idx);
    }

    int peaks(int l, int r) {
        // Пики считаем только внутри [l+1, r-1]
        if (l >= r) return 0;
        if (l+1 > r-1) return 0;
        return query(1, 0, size-1, l+1, r-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree tree(arr);

    int m;
    cin >> m;

    while (m--) {
        string cmd;
        cin >> cmd;

        if (cmd == "PEAK") {
            int l, r;
            cin >> l >> r;
            cout << tree.peaks(l, r) << "\n";
        }
        else if (cmd == "UPD") {
            int idx, val;
            cin >> idx >> val;
            tree.upd(idx, val);
        }
    }

    return 0;
}
