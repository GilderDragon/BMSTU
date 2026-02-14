#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// Функция вычисления префикс-функции для подстроки S
vector<int> computePrefixFunction(const string& pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

// Алгоритм Кнута-Морриса-Пратта для поиска всех вхождений
vector<int> KMPAllOccurrences(const string& text, const string& pattern) {
    vector<int> occurrences;

    // Если pattern пустой, возвращаем все позиции
    if (pattern.empty()) {
        for (size_t i = 0; i <= text.length(); i++) {
            occurrences.push_back(i);
        }
        return occurrences;
    }

    // Если text короче pattern, вхождений нет
    if (text.length() < pattern.length()) {
        return occurrences;
    }

    int n = text.length();
    int m = pattern.length();

    // Вычисляем префикс-функцию для pattern
    vector<int> pi = computePrefixFunction(pattern);

    int j = 0; // индекс в pattern

    for (int i = 0; i < n; i++) {
        // Продолжаем поиск с текущего состояния автомата
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }

        if (text[i] == pattern[j]) {
            j++;
        }

        // Если нашли полное вхождение pattern
        if (j == m) {
            // Добавляем позицию начала вхождения
            occurrences.push_back(i - m + 1);

            // Продолжаем поиск следующих вхождений
            // Используем префикс-функцию, чтобы не начинать с начала
            j = pi[j - 1];
        }
    }

    return occurrences;
}

// Альтернативная версия с более явным автоматом
vector<int> KMPAllOccurrencesAlternative(const string& text, const string& pattern) {
    vector<int> result;

    if (pattern.empty()) {
        // Если подстрока пустая, считаем что она входит везде
        for (size_t i = 0; i <= text.length(); i++) {
            result.push_back(i);
        }
        return result;
    }

    int n = text.length();
    int m = pattern.length();

    // Строим префикс-функцию
    vector<int> lps(m, 0); // longest prefix suffix

    // Вычисление lps[0..m-1] для pattern
    int len = 0; // длина предыдущего longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Поиск pattern в text
    i = 0; // индекс для text
    int j = 0; // индекс для pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Нашли вхождение
            result.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // Несовпадение после j совпадений
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return result;
}

// Функция для вывода результатов
void printOccurrences(const vector<int>& occurrences) {
    for (size_t i = 0; i < occurrences.size(); i++) {
        cout << occurrences[i];
        if (i < occurrences.size() - 1) {
            cout << " ";
        }
    }
    if (!occurrences.empty()) {
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cerr << "Использование: " << argv[0] << " <подстрока> <строка>" << endl;
        cerr << "Пример: " << argv[0] << " ab abcababcab" << endl;
        return 1;
    }

    string pattern = argv[1];
    string text = argv[2];

    // Поиск всех вхождений
    vector<int> occurrences = KMPAllOccurrences(text, pattern);

    // Вывод результатов
    printOccurrences(occurrences);

    return 0;
}
