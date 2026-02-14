#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Дерево отрезков для подсчета четности букв
class SegmentTree {
    vector<int> tree;  // битовая маска (26 бит для a-z)
    int size;

    // Объединяем две маски (XOR)
    int combine(int a, int b) {
        return a ^ b;  // XOR покажет, какие буквы нечетны
    }

    void build(string& s, int node, int l, int r) {
        if (l == r) {
            tree[node] = 1 << (s[l] - 'a');  // 1 бит для текущей буквы
            return;
        }
        int m = (l + r) / 2;
        build(s, node*2, l, m);
        build(s, node*2+1, m+1, r);
        tree[node] = combine(tree[node*2], tree[node*2+1]);
    }

    void update(int node, int l, int r, int idx, char ch) {
        if (l == r) {
            tree[node] = 1 << (ch - 'a');
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m) update(node*2, l, m, idx, ch);
        else update(node*2+1, m+1, r, idx, ch);
        tree[node] = combine(tree[node*2], tree[node*2+1]);
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        return combine(query(node*2, l, m, ql, qr),
                      query(node*2+1, m+1, r, ql, qr));
    }

public:
    SegmentTree(string& s) {
        size = s.length();
        tree.resize(4 * size);
        build(s, 1, 0, size-1);
    }

    void upd(int idx, char ch) {
        update(1, 0, size-1, idx, ch);
    }

    int get_mask(int l, int r) {
        return query(1, 0, size-1, l, r);
    }
};

// Проверяет, является ли подстрока гипердромом
bool is_hyperdrome(int mask) {
    // Подсчитываем сколько битов установлено (нечетные буквы)
    int odd_count = 0;
    for (int i = 0; i < 26; i++) {
        if (mask & (1 << i)) odd_count++;
    }
    // Гипердром: 0 или 1 нечетная буква
    return odd_count <= 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.length();

    SegmentTree tree(s);

    int m;
    cin >> m;

    while (m--) {
        string cmd;
        cin >> cmd;

        if (cmd == "HD") {
            int l, r;
            cin >> l >> r;
            int mask = tree.get_mask(l, r);
            cout << (is_hyperdrome(mask) ? "YES" : "NO") << "\n";
        }
        else if (cmd == "UPD") {
            int idx;
            string new_str;
            cin >> idx >> new_str;

            // Обновляем каждый символ по отдельности
            for (int i = 0; i < new_str.length(); i++) {
                if (idx + i < n) {  // Проверка границ
                    tree.upd(idx + i, new_str[i]);
                }
            }
        }
    }

    return 0;
}
