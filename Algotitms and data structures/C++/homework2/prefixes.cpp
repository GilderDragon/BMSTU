#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Вычисление префикс-функции для строки
vector<int> computePrefixFunction(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

// Функция для поиска периодических префиксов
void findPeriodicPrefixes(const string& s) {
    int n = s.length();
    vector<int> pi = computePrefixFunction(s);

    // Проходим по всем префиксам
    for (int i = 1; i < n; i++) {
        int prefixLength = i + 1; // Длина префикса (индексация с 0)
        int borderLength = pi[i]; // Длина максимального бордера

        // Длина возможного периода
        int periodLength = prefixLength - borderLength;

        // Проверяем, является ли префикс периодическим
        // Префикс периодический, если его длина делится на длину периода
        if (prefixLength % periodLength == 0) {
            int repetitions = prefixLength / periodLength;

            // Выводим результат, если повторений больше 1
            if (repetitions > 1) {
                cout << prefixLength << " " << repetitions << endl;
            }
        }
    }
}

// Альтернативная версия с более явной проверкой периодичности
void findPeriodicPrefixesAlternative(const string& s) {
    int n = s.length();
    vector<int> pi = computePrefixFunction(s);

    // Для каждого префикса проверяем периодичность
    for (int i = 0; i < n; i++) {
        int len = i + 1; // Длина текущего префикса

        // Длина максимального собственного суффикса, который является префиксом
        int borderLen = pi[i];

        // Длина возможного периода
        int periodLen = len - borderLen;

        // Проверяем два условия:
        // 1. Длина префикса делится на длину периода
        // 2. Длина периода действительно является периодом (дополнительная проверка)
        if (len % periodLen == 0 && borderLen >= len - periodLen) {
            int k = len / periodLen;

            // Выводим только если период повторяется хотя бы 2 раза
            if (k >= 2) {
                cout << len << " " << k << endl;
            }
        }
    }
}

// Версия с явной проверкой, что строка состоит из повторений периода
void findPeriodicPrefixesWithVerification(const string& s) {
    int n = s.length();
    vector<int> pi = computePrefixFunction(s);

    for (int i = 1; i < n; i++) {
        int len = i + 1;
        int period = len - pi[i];

        // Если длина делится на период, это кандидат
        if (len % period == 0) {
            bool isPeriodic = true;

            // Дополнительная проверка: действительно ли это период
            // Проверяем, что все символы соответствуют периоду
            for (int j = period; j < len; j++) {
                if (s[j] != s[j % period]) {
                    isPeriodic = false;
                    break;
                }
            }

            if (isPeriodic) {
                int k = len / period;
                if (k > 1) {
                    cout << len << " " << k << endl;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " <строка>" << endl;
        cerr << "Пример: " << argv[0] << " aabaabaabaab" << endl;
        return 1;
    }

    string s = argv[1];

    // Проверка, что строка не пустая
    if (s.empty()) {
        // Для пустой строки нет периодических префиксов
        return 0;
    }

    // Поиск и вывод периодических префиксов
    findPeriodicPrefixesWithVerification(s);

    return 0;
}
