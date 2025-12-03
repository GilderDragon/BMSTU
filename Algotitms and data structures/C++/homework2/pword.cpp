#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для вычисления префикс-функции
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

// Функция для построения автомата КМП (таблица переходов)
vector<vector<int>> buildKMPAutomaton(const string& pattern) {
    int m = pattern.length();
    vector<int> pi = computePrefixFunction(pattern);
    
    // Автомат: состояния 0..m, символы ASCII 0-127
    vector<vector<int>> automaton(m + 1, vector<int>(128, 0));
    
    // Базовые переходы
    automaton[0][pattern[0]] = 1;
    
    for (int state = 1; state <= m; state++) {
        // Копируем переходы из состояния pi[state-1]
        for (int c = 0; c < 128; c++) {
            automaton[state][c] = automaton[pi[state - 1]][c];
        }
        
        // Если не конечное состояние, устанавливаем переход по следующему символу
        if (state < m) {
            automaton[state][pattern[state]] = state + 1;
        }
    }
    
    return automaton;
}

// Основная функция: проверка, составлена ли T из префиксов S
bool isComposedOfPrefixes(const string& S, const string& T) {
    int n = T.length();
    int m = S.length();
    
    // Если T пустая, она считается составленной из префиксов (пустой префикс)
    if (n == 0) {
        return true;
    }
    
    // Если S пустая, а T нет, то T не может быть составлена из префиксов S
    if (m == 0) {
        return false;
    }
    
    // Строим автомат КМП для строки S
    vector<vector<int>> automaton = buildKMPAutomaton(S);
    
    int currentState = 0;
    
    // Проходим по строке T
    for (int i = 0; i < n; i++) {
        char c = T[i];
        
        // Переход в автомате
        currentState = automaton[currentState][c];
        
        // Если достигли состояния 0 (нет совпадения с началом S)
        // или если текущий символ не является продолжением текущего префикса
        if (currentState == 0) {
            // Проверяем, можно ли начать новый префикс с этого символа
            currentState = automaton[0][c];
            if (currentState == 0) {
                return false; // Символ не соответствует ни одному префиксу S
            }
        }
    }
    
    return true;
}

// Альтернативный подход: проверка через суффиксный автомат (более эффективный)
bool isComposedOfPrefixesAlternative(const string& S, const string& T) {
    int n = T.length();
    int m = S.length();
    
    if (n == 0) return true;
    if (m == 0) return false;
    
    // Строим массив всех префиксов S
    // unordered_set для быстрой проверки, но нам нужно проверять не только полные префиксы,
    // но и частичные совпадения
    
    // Лучший подход: автомат на префиксах
    vector<bool> isPrefixState(m + 1, false);
    for (int i = 0; i <= m; i++) {
        isPrefixState[i] = true; // Все состояния от 0 до m - это префиксы S
    }
    
    // Вычисляем префикс-функцию для S
    vector<int> pi = computePrefixFunction(S);
    
    // Проходим по T, моделируя KMP
    int currentState = 0;
    
    for (int i = 0; i < n; i++) {
        char c = T[i];
        
        // Пытаемся продлить текущее совпадение
        while (currentState > 0 && (currentState == m || S[currentState] != c)) {
            currentState = pi[currentState - 1];
        }
        
        if (currentState < m && S[currentState] == c) {
            currentState++;
        } else if (currentState == 0 && S[0] != c) {
            // Не можем начать ни один префикс с этого символа
            return false;
        }
        
        // Если мы здесь, значит currentState - это длина текущего совпавшего префикса
        // Все такие состояния допустимы (0..m)
    }
    
    return true;
}

// Простой жадный алгоритм (самый понятный)
bool isComposedOfPrefixesSimple(const string& S, const string& T) {
    int n = T.length();
    int m = S.length();
    
    if (n == 0) return true;
    if (m == 0) return false;
    
    int i = 0; // Позиция в T
    
    while (i < n) {
        // Пытаемся найти самый длинный префикс S, который совпадает с началом T[i..]
        bool found = false;
        
        // Проверяем все возможные длины префиксов от 1 до m
        // Начиная с самого длинного возможного
        for (int len = min(m, n - i); len >= 1; len--) {
            // Сравниваем префикс S длины len с подстрокой T начиная с i
            if (S.compare(0, len, T, i, len) == 0) {
                i += len; // Перемещаемся вперед на длину префикса
                found = true;
                break;
            }
        }
        
        if (!found) {
            return false; // Не нашли подходящий префикс
        }
    }
    
    return true;
}

// Оптимизированная версия с префикс-функцией и автоматом
bool isComposedOfPrefixesOptimized(const string& S, const string& T) {
    int n = T.length();
    int m = S.length();
    
    if (n == 0) return true;
    if (m == 0) return false;
    
    // Строим префикс-функцию для S
    vector<int> pi = computePrefixFunction(S);
    
    // Состояние автомата - текущая длина совпавшего префикса S
    int state = 0;
    
    for (int i = 0; i < n; i++) {
        char c = T[i];
        
        // Пытаемся продлить текущее совпадение
        if (state < m && S[state] == c) {
            state++;
        } else {
            // Используем префикс-функцию для поиска нового состояния
            while (state > 0 && S[state] != c) {
                state = pi[state - 1];
            }
            
            if (S[state] == c) {
                state++;
            } else {
                // Проверяем, можно ли начать с начала
                if (S[0] == c) {
                    state = 1;
                } else {
                    return false;
                }
            }
        }
        
        // Если достигли конца S, сбрасываем состояние для поиска следующего префикса
        if (state == m) {
            state = pi[state - 1]; // Можно продолжить с максимального бордера
        }
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cerr << "Использование: " << argv[0] << " <строка_S> <строка_T>" << endl;
        cerr << "Пример: " << argv[0] << " abracadabra abrabracada" << endl;
        return 1;
    }
    
    string S = argv[1];
    string T = argv[2];
    
    // Проверка условия
    bool result = isComposedOfPrefixesOptimized(S, T);
    
    // Вывод результата
    cout << (result ? "yes" : "no") << endl;
    
    return 0;
}
