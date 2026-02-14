#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Максимальный размер алфавита (ASCII)
const int ALPHABET_SIZE = 256;

// Класс для расширенной эвристики стоп-символа
class ExtendedBoyerMoore {
private:
    string pattern;
    int m; // длина pattern
    vector<vector<int>> delta1; // матрица смещений δ1[i][c]

public:
    ExtendedBoyerMoore(const string& pat) : pattern(pat), m(pat.length()) {
        preprocessExtendedStopSymbol();
    }

    // Препроцессинг для расширенной эвристики стоп-символа
    void preprocessExtendedStopSymbol() {
        // Инициализируем матрицу размером m x ALPHABET_SIZE
        // Значение по умолчанию: m (сдвиг на длину pattern)
        delta1.assign(m, vector<int>(ALPHABET_SIZE, m));

        // Для каждой позиции i в pattern
        for (int i = 0; i < m; i++) {
            // Для каждого символа c в алфавите
            for (int c = 0; c < ALPHABET_SIZE; c++) {
                // Ищем последнее вхождение символа c в pattern слева от i
                int lastPos = -1;

                // Ищем справа налево от i-1 до 0
                for (int j = i - 1; j >= 0; j--) {
                    if (pattern[j] == c) {
                        lastPos = j;
                        break;
                    }
                }

                if (lastPos != -1) {
                    // Нашли символ c левее i
                    delta1[i][c] = i - lastPos; // сколько нужно сдвинуть
                } else {
                    // Символ c не найден левее i
                    // В классическом Бойере-Муре это было бы m
                    // Но здесь мы хотим сдвинуть так, чтобы i совместился с k
                    // Если символа нет левее i, сдвигаем на i+1
                    delta1[i][c] = i + 1;
                }
            }
        }

        // Оптимизация: для символов, которые вообще не встречаются в pattern
        // устанавливаем сдвиг m (как в классическом алгоритме)
        vector<bool> charInPattern(ALPHABET_SIZE, false);
        for (int i = 0; i < m; i++) {
            charInPattern[(unsigned char)pattern[i]] = true;
        }

        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (!charInPattern[c]) {
                for (int i = 0; i < m; i++) {
                    delta1[i][c] = i + 1; // или m, но i+1 корректнее
                }
            }
        }
    }

    // Поиск первого вхождения pattern в text
    int searchFirst(const string& text) {
        int n = text.length();

        if (m == 0) {
            return 0; // Пустая строка всегда в начале
        }

        if (n < m) {
            return n; // pattern длиннее text
        }

        int i = 0; // позиция в text (начало текущего окна)

        while (i <= n - m) {
            // Сравниваем с конца pattern
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[i + j]) {
                j--;
            }

            if (j < 0) {
                // Нашли вхождение
                return i;
            } else {
                // Применяем расширенную эвристику стоп-символа
                char stopChar = text[i + j];
                int shift = delta1[j][(unsigned char)stopChar];

                // Гарантируем, что сдвиг хотя бы 1
                shift = max(shift, 1);

                i += shift;
            }
        }

        return n; // не нашли
    }

    // Альтернативная реализация с более эффективным препроцессингом
    void preprocessOptimized() {
        delta1.assign(m, vector<int>(ALPHABET_SIZE, m));

        // Для каждого символа в алфавите запоминаем его позиции в pattern
        vector<vector<int>> charPositions(ALPHABET_SIZE);

        // Собираем позиции символов
        for (int i = 0; i < m; i++) {
            charPositions[(unsigned char)pattern[i]].push_back(i);
        }

        // Заполняем матрицу delta1
        for (int i = 0; i < m; i++) {
            for (int c = 0; c < ALPHABET_SIZE; c++) {
                // Ищем максимальную позицию < i для символа c
                int lastPos = -1;

                // Используем бинарный поиск в отсортированном массиве позиций
                const vector<int>& positions = charPositions[c];

                // Позиции уже отсортированы по возрастанию
                // Нам нужна последняя позиция, меньшая i
                if (!positions.empty()) {
                    // Ищем вручную (так как массив небольшой)
                    for (int idx = positions.size() - 1; idx >= 0; idx--) {
                        if (positions[idx] < i) {
                            lastPos = positions[idx];
                            break;
                        }
                    }
                }

                if (lastPos != -1) {
                    delta1[i][c] = i - lastPos;
                } else {
                    // Символ не встречается левее i
                    // Проверяем, встречается ли вообще в pattern
                    if (charPositions[c].empty()) {
                        delta1[i][c] = i + 1; // или m
                    } else {
                        // Символ есть в pattern, но только справа от i
                        delta1[i][c] = m; // классический сдвиг
                    }
                }
            }
        }
    }
};

// Упрощенная версия без класса
int extendedBoyerMooreSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        return 0;
    }

    if (n < m) {
        return n;
    }

    // Создаем и заполняем матрицу δ1
    vector<vector<int>> delta1(m, vector<int>(ALPHABET_SIZE, m));

    // Простой способ заполнения (O(m^2 * |Σ|))
    for (int i = 0; i < m; i++) {
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            // Ищем символ c в pattern[0..i-1]
            bool found = false;
            for (int j = i - 1; j >= 0; j--) {
                if (pattern[j] == c) {
                    delta1[i][c] = i - j;
                    found = true;
                    break;
                }
            }

            if (!found) {
                // Символ не найден левее i
                delta1[i][c] = i + 1; // минимальный сдвиг
            }
        }
    }

    // Поиск
    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        // Сравниваем с конца
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            return i; // Нашли
        } else {
            // Применяем расширенную эвристику
            unsigned char stopChar = text[i + j];
            int shift = delta1[j][stopChar];

            // Гарантируем положительный сдвиг
            if (shift <= 0) shift = 1;

            i += shift;
        }
    }

    return n; // Не нашли
}

// Оптимизированная версия с более быстрым препроцессингом
int extendedBoyerMooreOptimized(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;
    if (n < m) return n;

    // Вектор для хранения последней позиции каждого символа слева от i
    vector<int> lastPos(ALPHABET_SIZE, -1);

    // Основной цикл поиска
    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        // Сравниваем с конца
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            return i; // Нашли
        } else {
            unsigned char stopChar = text[i + j];

            // Вычисляем сдвиг на лету
            int shift = 1; // минимальный сдвиг

            // Ищем символ stopChar в pattern[0..j-1]
            bool found = false;
            for (int k = j - 1; k >= 0; k--) {
                if (pattern[k] == stopChar) {
                    shift = j - k;
                    found = true;
                    break;
                }
            }

            // Если не нашли, сдвигаем на j+1
            if (!found) {
                shift = j + 1;
            }

            i += shift;
        }
    }

    return n;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cerr << "Использование: " << argv[0] << " <подстрока> <строка>" << endl;
        cerr << "Пример: " << argv[0] << " aba babacabac" << endl;
        return 1;
    }

    string pattern = argv[1];
    string text = argv[2];

    // Поиск с расширенной эвристикой стоп-символа
    int result = extendedBoyerMooreOptimized(text, pattern);

    // Вывод результата
    cout << result << endl;

    return 0;
}
