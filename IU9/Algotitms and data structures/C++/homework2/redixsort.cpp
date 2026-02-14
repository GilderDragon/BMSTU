#include <iostream>
#include <vector>

using namespace std;

// Объединение для доступа к отдельным байтам 32-битного целого числа
union Int32 {
    int x;
    unsigned char bytes[4];

    // Конструкторы
    Int32() : x(0) {}
    Int32(int value) : x(value) {}

    // Оператор присваивания
    Int32& operator=(int value) {
        x = value;
        return *this;
    }

    // Оператор приведения к int
    operator int() const {
        return x;
    }
};

// Функция для получения знакового байта с учетом дополнения до двух
int getSignedByte(const Int32& num, int bytePos) {
    if (bytePos == 3) { // Старший байт (знаковый)
        // Инвертируем старший бит для корректной сортировки знаковых чисел
        return (num.bytes[bytePos] ^ 0x80); // XOR с 0x80 инвертирует старший бит
    }
    return num.bytes[bytePos];
}

// Функция для восстановления оригинального значения
void restoreSign(Int32& num) {
    // Инвертируем старший бит обратно
    num.bytes[3] ^= 0x80;
}

// Поразрядная сортировка по байтам (основание 256)
void radixSortLSD(vector<Int32>& arr) {
    if (arr.empty()) return;

    const int n = arr.size();
    const int BASE = 256; // Основание системы счисления (байт = 256 значений)
    const int BYTES_COUNT = 4; // 4 байта в 32-битном целом

    vector<Int32> output(n);

    // Сортируем по каждому байту, начиная с младшего (LSD)
    for (int bytePos = 0; bytePos < BYTES_COUNT; bytePos++) {
        // Массив для подсчета частот (0-255)
        vector<int> count(BASE, 0);

        // Подсчитываем частоты для текущего байта
        for (int i = 0; i < n; i++) {
            // Для знаковых чисел корректируем старший байт
            int byteValue = (bytePos == 3) ? getSignedByte(arr[i], bytePos) : arr[i].bytes[bytePos];
            count[byteValue]++;
        }

        // Преобразуем count так, чтобы он содержал позиции
        for (int i = 1; i < BASE; i++) {
            count[i] += count[i - 1];
        }

        // Строим выходной массив (с конца для стабильности)
        for (int i = n - 1; i >= 0; i--) {
            // Для знаковых чисел корректируем старший байт
            int byteValue = (bytePos == 3) ? getSignedByte(arr[i], bytePos) : arr[i].bytes[bytePos];
            output[count[byteValue] - 1] = arr[i];
            count[byteValue]--;
        }

        // Копируем отсортированный массив обратно
        arr = output;
    }

    // Восстанавливаем знаки после сортировки
    for (auto& num : arr) {
        restoreSign(num);
    }
}

// Альтернативная версия: сортировка с использованием сдвига и маски
void radixSortLSDAlternative(vector<Int32>& arr) {
    if (arr.empty()) return;

    const int n = arr.size();
    vector<Int32> output(n);

    // Создаем временный массив для преобразования чисел
    vector<unsigned int> temp(n);
    for (int i = 0; i < n; i++) {
        // Преобразуем знаковое в беззнаковое с учетом порядка
        temp[i] = arr[i].x ^ 0x80000000; // Инвертируем знаковый бит
    }

    // Сортируем по каждому байту (0-3)
    for (int bytePos = 0; bytePos < 4; bytePos++) {
        vector<int> count(256, 0);

        // Подсчет частот
        for (int i = 0; i < n; i++) {
            int byteValue = (temp[i] >> (bytePos * 8)) & 0xFF;
            count[byteValue]++;
        }

        // Преобразование в позиции
        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }

        // Построение выходного массива
        vector<unsigned int> tempOutput(n);
        for (int i = n - 1; i >= 0; i--) {
            int byteValue = (temp[i] >> (bytePos * 8)) & 0xFF;
            tempOutput[count[byteValue] - 1] = temp[i];
            count[byteValue]--;
        }

        temp = tempOutput;
    }

    // Преобразуем обратно в знаковые числа
    for (int i = 0; i < n; i++) {
        arr[i].x = temp[i] ^ 0x80000000; // Восстанавливаем знаковый бит
    }
}

// Еще одна версия: прямая работа с объединением
void radixSortDirect(vector<Int32>& arr) {
    if (arr.empty()) return;

    const int n = arr.size();
    vector<Int32> output(n);

    // Сортируем по каждому байту
    for (int bytePos = 0; bytePos < 4; bytePos++) {
        vector<int> count(256, 0);

        // Для знаковых чисел: корректируем старший байт
        if (bytePos == 3) {
            // Старший байт (знаковый) - корректируем для сортировки
            for (int i = 0; i < n; i++) {
                int byteValue = arr[i].bytes[bytePos] ^ 0x80; // Инвертируем старший бит
                count[byteValue]++;
            }
        } else {
            // Младшие байты - сортируем как есть
            for (int i = 0; i < n; i++) {
                count[arr[i].bytes[bytePos]]++;
            }
        }

        // Преобразуем count в позиции
        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }

        // Строим выходной массив
        for (int i = n - 1; i >= 0; i--) {
            int byteValue;
            if (bytePos == 3) {
                byteValue = arr[i].bytes[bytePos] ^ 0x80;
            } else {
                byteValue = arr[i].bytes[bytePos];
            }

            output[count[byteValue] - 1] = arr[i];
            count[byteValue]--;
        }

        // Копируем обратно
        arr = output;
    }

    // Восстанавливаем знаки
    for (auto& num : arr) {
        num.bytes[3] ^= 0x80;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    // Чтение количества элементов
    if (!(cin >> n) || n < 0) {
        cerr << "Ошибка: неверное количество элементов" << endl;
        return 1;
    }

    vector<Int32> arr(n);

    // Чтение элементов
    for (int i = 0; i < n; i++) {
        int value;
        if (!(cin >> value)) {
            cerr << "Ошибка: неверный формат данных" << endl;
            return 1;
        }
        arr[i] = value;
    }

    // Если элементов нет или один, просто выводим
    if (n <= 1) {
        for (const auto& num : arr) {
            cout << num.x << " ";
        }
        if (n > 0) cout << endl;
        return 0;
    }

    // Выбор метода сортировки
    radixSortDirect(arr);

    // Вывод отсортированного массива
    for (int i = 0; i < n; i++) {
        cout << arr[i].x;
        if (i < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
