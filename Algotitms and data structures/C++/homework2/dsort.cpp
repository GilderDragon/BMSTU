#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Алгоритм сортировки подсчетом (сортировка распределением)
// для строки, состоящей только из строчных латинских букв
string countingSort(const string& str) {
    // Создаем массив для подсчета частот букв (26 строчных латинских букв)
    int freq[26] = {0};

    // Подсчитываем частоту каждой буквы
    for (char c : str) {
        freq[c - 'a']++;
    }

    // Строим отсортированную строку
    string sortedStr;
    sortedStr.reserve(str.length()); // резервируем память для эффективности

    for (int i = 0; i < 26; i++) {
        // Добавляем букву 'a' + i столько раз, сколько она встретилась
        sortedStr.append(freq[i], 'a' + i);
    }

    return sortedStr;
}

// Оптимизированная версия с использованием указателей (для больших строк)
string countingSortOptimized(const string& str) {
    const int n = str.length();

    if (n == 0) return "";

    // Подсчет частот
    int freq[26] = {0};

    for (int i = 0; i < n; i++) {
        freq[str[i] - 'a']++;
    }

    // Вычисляем префиксные суммы (кумулятивные суммы)
    for (int i = 1; i < 26; i++) {
        freq[i] += freq[i - 1];
    }

    // Создаем выходную строку
    string result(n, ' ');

    // Заполняем строку в обратном порядке для сохранения стабильности
    // (хотя для этой задачи стабильность не важна)
    for (int i = n - 1; i >= 0; i--) {
        int index = str[i] - 'a';
        result[--freq[index]] = str[i];
    }

    return result;
}

// Альтернативная версия с использованием вектора
string distributionSort(const string& str) {
    if (str.empty()) return "";

    // Вектор для подсчета частот
    vector<int> count(26, 0);

    // Подсчет частот
    for (char c : str) {
        count[c - 'a']++;
    }

    // Формирование результата
    string result;
    result.reserve(str.length());

    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            result.append(count[i], static_cast<char>('a' + i));
        }
    }

    return result;
}

int main() {
    // Для работы со строками до миллиона символов
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;

    // Чтение строки из стандартного потока ввода
    // Используем getline для чтения всей строки
    if (!getline(cin, input)) {
        cerr << "Ошибка чтения строки" << endl;
        return 1;
    }

    // Проверяем, что строка не пустая
    if (input.empty()) {
        cout << endl;
        return 0;
    }

    // Верификация, что строка содержит только строчные латинские буквы
    // (по условию задачи это гарантируется, но для надежности можно проверить)
    #ifdef DEBUG
    for (char c : input) {
        if (c < 'a' || c > 'z') {
            cerr << "Ошибка: строка содержит недопустимые символы" << endl;
            return 1;
        }
    }
    #endif

    // Выбираем метод сортировки в зависимости от размера строки
    string sorted;

    if (input.length() < 1000000) {
        // Для строк до миллиона используем простой метод
        sorted = countingSort(input);
    } else {
        // Для очень больших строк используем оптимизированную версию
        sorted = countingSortOptimized(input);
    }

    // Вывод результата
    cout << sorted << endl;

    return 0;
}
