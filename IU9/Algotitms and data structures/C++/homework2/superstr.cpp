#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Функция для вычисления максимального перекрытия между двумя строками
int compute_overlap(const string& a, const string& b) {
    int max_len = min(a.length(), b.length());
    // Проверяем все возможные длины перекрытия от максимальной до 1
    for (int len = max_len; len > 0; len--) {
        if (a.substr(a.length() - len) == b.substr(0, len)) {
            return len;
        }
    }
    return 0;
}

int main() {
    int n;
    cin >> n;

    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }

    // Вычисляем матрицу перекрытий между всеми парами строк
    vector<vector<int>> overlap(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                overlap[i][j] = compute_overlap(strings[i], strings[j]);
            }
        }
    }

    // Инициализация DP
    int total_masks = 1 << n;  // 2^n возможных масок
    vector<vector<int>> dp(total_masks, vector<int>(n, INT_MAX));

    // Базовые случаи: каждая строка сама по себе
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = strings[i].length();
    }

    // Заполнение DP таблицы
    for (int mask = 0; mask < total_masks; mask++) {
        for (int last = 0; last < n; last++) {
            // Если это состояние недостижимо, пропускаем
            if (dp[mask][last] == INT_MAX) continue;

            // Пробуем добавить каждую еще не использованную строку
            for (int next_str = 0; next_str < n; next_str++) {
                if (mask & (1 << next_str)) continue;  // строка уже использована

                int new_mask = mask | (1 << next_str);
                int new_length = dp[mask][last] + strings[next_str].length() - overlap[last][next_str];

                if (new_length < dp[new_mask][next_str]) {
                    dp[new_mask][next_str] = new_length;
                }
            }
        }
    }

    // Находим минимальную длину среди всех полных масок
    int answer = INT_MAX;
    int full_mask = (1 << n) - 1;
    for (int last = 0; last < n; last++) {
        if (dp[full_mask][last] < answer) {
            answer = dp[full_mask][last];
        }
    }

    cout << answer << endl;

    return 0;
}
