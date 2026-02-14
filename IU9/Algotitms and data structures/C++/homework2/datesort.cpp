#include <iostream>
#include <vector>

using namespace std;

// Структура для хранения даты
struct Date {
    int Day;
    int Month;
    int Year;

    // Конструктор для удобства
    Date(int y = 1970, int m = 1, int d = 1) : Year(y), Month(m), Day(d) {}
};

// Функция для сравнения дат (для проверки)
bool operator<(const Date& a, const Date& b) {
    if (a.Year != b.Year) return a.Year < b.Year;
    if (a.Month != b.Month) return a.Month < b.Month;
    return a.Day < b.Day;
}

// Функция для проверки корректности даты
bool isValidDate(const Date& date) {
    if (date.Year < 1970 || date.Year > 2030) return false;
    if (date.Month < 1 || date.Month > 12) return false;
    if (date.Day < 1 || date.Day > 31) return false;

    // Проверка дней в месяце
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверка високосного года для февраля
    if (date.Month == 2) {
        bool isLeap = (date.Year % 4 == 0 && date.Year % 100 != 0) || (date.Year % 400 == 0);
        if (date.Day > (isLeap ? 29 : 28)) return false;
    } else if (date.Day > daysInMonth[date.Month - 1]) {
        return false;
    }

    return true;
}

// Функция для получения максимального значения в массиве дат по заданному разряду
int getMaxDateValue(const vector<Date>& dates, int (*getter)(const Date&)) {
    int maxVal = 0;
    for (const auto& date : dates) {
        int val = getter(date);
        if (val > maxVal) maxVal = val;
    }
    return maxVal;
}

// Функции для извлечения разрядов даты
int getDay(const Date& date) { return date.Day; }
int getMonth(const Date& date) { return date.Month; }
int getYear(const Date& date) { return date.Year; }

// Функция сортировки подсчетом для одного разряда
void countingSortByDigit(vector<Date>& dates, vector<Date>& output,
                         int (*getter)(const Date&), int exp) {
    const int BASE = 10; // Основание системы счисления (десятичная)

    // Создаем массив для подсчета частот (0-9)
    vector<int> count(BASE, 0);

    // Подсчитываем частоты для текущего разряда
    for (const auto& date : dates) {
        int digit = (getter(date) / exp) % BASE;
        count[digit]++;
    }

    // Преобразуем count так, чтобы он содержал позиции
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }

    // Строим выходной массив (с конца для стабильности)
    for (int i = dates.size() - 1; i >= 0; i--) {
        int digit = (getter(dates[i]) / exp) % BASE;
        output[count[digit] - 1] = dates[i];
        count[digit]--;
    }

    // Копируем отсортированный массив обратно
    dates = output;
}

// Функция поразрядной сортировки для дат
void radixSortDates(vector<Date>& dates) {
    if (dates.empty()) return;

    vector<Date> output(dates.size());

    // Сортируем по дням (1-31, максимальное значение 31)
    // Для дней используем основание 32 (0-31)
    int maxDay = getMaxDateValue(dates, getDay);
    for (int exp = 1; maxDay / exp > 0; exp *= 10) {
        countingSortByDigit(dates, output, getDay, exp);
    }

    // Сортируем по месяцам (1-12, максимальное значение 12)
    // Для месяцев используем основание 10
    int maxMonth = getMaxDateValue(dates, getMonth);
    for (int exp = 1; maxMonth / exp > 0; exp *= 10) {
        countingSortByDigit(dates, output, getMonth, exp);
    }

    // Сортируем по годам (1970-2030, максимальное значение 2030)
    // Для годов используем основание 10
    int maxYear = getMaxDateValue(dates, getYear);
    for (int exp = 1; maxYear / exp > 0; exp *= 10) {
        countingSortByDigit(dates, output, getYear, exp);
    }
}

// Альтернативная версия: поразрядная сортировка с разными основаниями
// В этом варианте мы сначала сортируем по младшим разрядам (день),
// затем по средним (месяц), затем по старшим (год)
void radixSortDatesWithDifferentBases(vector<Date>& dates) {
    if (dates.empty()) return;

    int n = dates.size();
    vector<Date> output(n);

    // Основания систем счисления для каждого поля
    const int baseDay = 32;    // Дни: 1-31, но используем 32 для 0-31
    const int baseMonth = 13;  // Месяцы: 1-12, но используем 13 для 0-12
    const int baseYear = 61;   // Годы: 1970-2030 (диапазон 61 год)

    // Функция для сортировки подсчетом с заданным основанием
    auto countingSort = [&](int (*getter)(const Date&), int base) {
        vector<int> count(base, 0);

        // Подсчет частот
        for (const auto& date : dates) {
            int value = getter(date);
            count[value]++;
        }

        // Преобразование в позиции
        for (int i = 1; i < base; i++) {
            count[i] += count[i - 1];
        }

        // Построение выходного массива (с конца для стабильности)
        for (int i = n - 1; i >= 0; i--) {
            int value = getter(dates[i]);
            output[count[value] - 1] = dates[i];
            count[value]--;
        }

        // Копирование обратно
        dates = output;
    };

    // Сортировка по дням (с основанием 32)
    countingSort(getDay, baseDay);

    // Сортировка по месяцам (с основанием 13)
    countingSort(getMonth, baseMonth);

    // Сортировка по годам (с основанием 61, но нужно нормализовать)
    // Нормализуем годы: 1970 -> 0, 1971 -> 1, ..., 2030 -> 60
    auto getNormalizedYear = [](const Date& date) {
        return date.Year - 1970;
    };

    countingSort([](const Date& date) {
        return date.Year - 1970;
    }, 61);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    // Чтение количества дат
    if (!(cin >> n) || n < 0) {
        cerr << "Ошибка: неверное количество дат" << endl;
        return 1;
    }

    vector<Date> dates(n);

    // Чтение дат
    for (int i = 0; i < n; i++) {
        int y, m, d;
        if (!(cin >> y >> m >> d)) {
            cerr << "Ошибка: неверный формат даты" << endl;
            return 1;
        }

        dates[i] = Date(y, m, d);

        // Проверка корректности даты (опционально, по условию даты корректны)
        if (!isValidDate(dates[i])) {
            cerr << "Предупреждение: дата " << y << " " << m << " " << d
                 << " может быть некорректной" << endl;
        }
    }

    // Если дат нет или одна, просто выводим
    if (n <= 1) {
        for (const auto& date : dates) {
            cout << date.Year << " " << date.Month << " " << date.Day << endl;
        }
        return 0;
    }

    // Сортировка поразрядным методом
    radixSortDatesWithDifferentBases(dates);

    // Вывод отсортированных дат
    for (const auto& date : dates) {
        cout << date.Year << " " << date.Month << " " << date.Day << endl;
    }

    return 0;
}
