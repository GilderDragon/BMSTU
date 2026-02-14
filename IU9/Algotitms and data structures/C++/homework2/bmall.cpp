#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// Максимальный размер алфавита (ASCII)
const int ALPHABET_SIZE = 256;

// Класс для алгоритма Бойера-Мура
class BoyerMoore {
private:
    string pattern;
    int m; // длина pattern
    vector<int> badCharShift; // таблица плохого символа
    vector<int> goodSuffixShift; // таблица хорошего суффикса
    vector<int> suffix; // вспомогательный массив для хорошего суффикса

public:
    BoyerMoore(const string& pat) : pattern(pat), m(pat.length()) {
        preprocessBadChar();
        preprocessGoodSuffix();
    }

    // Препроцессинг таблицы плохого символа
    void preprocessBadChar() {
        badCharShift.resize(ALPHABET_SIZE, m);

        // Для символов в pattern устанавливаем сдвиг от конца
        for (int i = 0; i < m - 1; i++) {
            badCharShift[(unsigned char)pattern[i]] = m - 1 - i;
        }
    }

    // Вспомогательная функция для препроцессинга хорошего суффикса
    void computeSuffix() {
        suffix.resize(m, 0);
        suffix[m - 1] = m;

        int g = m - 1;
        int f = 0;

        for (int i = m - 2; i >= 0; i--) {
            if (i > g && suffix[i + m - 1 - f] < i - g) {
                suffix[i] = suffix[i + m - 1 - f];
            } else {
                if (i < g) {
                    g = i;
                }
                f = i;

                while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                    g--;
                }
                suffix[i] = f - g;
            }
        }
    }

    // Препроцессинг таблицы хорошего суффикса
    void preprocessGoodSuffix() {
        goodSuffixShift.resize(m + 1, m);
        computeSuffix();

        // Первый случай: суффикс появляется в pattern слева от текущей позиции
        int j = 0;
        for (int i = m - 1; i >= -1; i--) {
            if (i == -1 || suffix[i] == i + 1) {
                while (j < m - 1 - i) {
                    if (goodSuffixShift[j] == m) {
                        goodSuffixShift[j] = m - 1 - i;
                    }
                    j++;
                }
            }
        }

        // Второй случай: суффикс совпадает с префиксом
        for (int i = 0; i < m - 1; i++) {
            goodSuffixShift[m - 1 - suffix[i]] = m - 1 - i;
        }
    }

    // Поиск всех вхождений pattern в text
    vector<int> searchAll(const string& text) {
        vector<int> occurrences;
        int n = text.length();

        if (m == 0) {
            // Пустой pattern совпадает везде
            for (int i = 0; i <= n; i++) {
                occurrences.push_back(i);
            }
            return occurrences;
        }

        if (n < m) {
            return occurrences; // pattern длиннее text
        }

        int i = 0; // позиция в text

        while (i <= n - m) {
            int j = m - 1; // идем с конца pattern

            // Сравниваем с конца
            while (j >= 0 && pattern[j] == text[i + j]) {
                j--;
            }

            if (j < 0) {
                // Нашли вхождение
                occurrences.push_back(i);

                // Сдвиг для продолжения поиска
                i += goodSuffixShift[0];
            } else {
                // Используем максимум из сдвигов плохого символа и хорошего суффикса
                int badCharShiftVal = badCharShift[(unsigned char)text[i + j]] - (m - 1 - j);
                int goodSuffixShiftVal = goodSuffixShift[j + 1];

                i += max(badCharShiftVal, goodSuffixShiftVal);
            }
        }

        return occurrences;
    }

    // Упрощенная версия с только таблицей плохого символа (упрощенный Бойер-Мур)
    vector<int> searchAllSimple(const string& text) {
        vector<int> occurrences;
        int n = text.length();

        if (m == 0) {
            for (int i = 0; i <= n; i++) {
                occurrences.push_back(i);
            }
            return occurrences;
        }

        if (n < m) {
            return occurrences;
        }

        // Упрощенная таблица плохого символа
        vector<int> badChar(ALPHABET_SIZE, m);
        for (int i = 0; i < m - 1; i++) {
            badChar[(unsigned char)pattern[i]] = m - 1 - i;
        }

        int i = 0;
        while (i <= n - m) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[i + j]) {
                j--;
            }

            if (j < 0) {
                // Нашли вхождение
                occurrences.push_back(i);
                i++; // Простой сдвиг на 1 для поиска следующего вхождения
            } else {
                // Сдвиг по плохому символу
                int shift = badChar[(unsigned char)text[i + j]] - (m - 1 - j);
                i += max(1, shift); // Минимальный сдвиг 1
            }
        }

        return occurrences;
    }
};

// Функция для упрощенного алгоритма Бойера-Мура (только плохой символ)
vector<int> boyerMooreSearch(const string& text, const string& pattern) {
    vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        for (int i = 0; i <= n; i++) {
            occurrences.push_back(i);
        }
        return occurrences;
    }

    if (n < m) {
        return occurrences;
    }

    // Таблица плохого символа
    vector<int> badChar(ALPHABET_SIZE, m);

    // Заполняем таблицу: для символов в pattern
    for (int i = 0; i < m - 1; i++) {
        badChar[(unsigned char)pattern[i]] = m - 1 - i;
    }

    int i = 0; // индекс в text

    while (i <= n - m) {
        int j = m - 1; // индекс в pattern

        // Сравниваем с конца pattern
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            // Нашли вхождение
            occurrences.push_back(i);

            // Сдвигаем для поиска следующего вхождения
            // Можно сдвинуть на 1 или на m (если нет перекрытий)
            i += (m > 1) ? m : 1;
        } else {
            // Вычисляем сдвиг по плохому символу
            int shift = badChar[(unsigned char)text[i + j]] - (m - 1 - j);
            i += max(1, shift); // Минимальный сдвиг 1
        }
    }

    return occurrences;
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
        cerr << "Пример: " << argv[0] << " abc abcabcabc" << endl;
        return 1;
    }

    string pattern = argv[1];
    string text = argv[2];

    // Используем упрощенную версию (только таблица плохого символа)
    vector<int> occurrences = boyerMooreSearch(text, pattern);

    // Вывод результатов
    printOccurrences(occurrences);

    return 0;
}
