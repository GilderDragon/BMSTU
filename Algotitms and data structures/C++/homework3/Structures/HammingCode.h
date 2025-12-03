#ifndef BMSTU_HAMMINGCODE_H
#define BMSTU_HAMMINGCODE_H
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <stdexcept>
#include <string>

class HammingCode {
private:
    int m; // количество информационных бит
    int r; // количество проверочных бит
    int n; // общая длина кодового слова (n = m + r)

    // Вычисление количества проверочных бит для заданного m
    int calculateRedundantBits(int dataBits) const {
        int r = 0;
        while (std::pow(2, r) < dataBits + r + 1) {
            r++;
        }
        return r;
    }

    // Позиции проверочных бит (степени двойки)
    bool isParityPosition(int pos) const {
        return (pos & (pos - 1)) == 0;
    }

public:
    HammingCode(int dataBits) : m(dataBits) {
        if (dataBits <= 0) {
            throw std::invalid_argument("Количество информационных бит должно быть положительным");
        }

        r = calculateRedundantBits(m);
        n = m + r;

        std::cout << "Код Хэмминга (" << n << ", " << m << ")" << std::endl;
        std::cout << "Информационных бит: " << m << std::endl;
        std::cout << "Проверочных бит: " << r << std::endl;
        std::cout << "Общая длина: " << n << std::endl;
        std::cout << "Минимальное расстояние: 3" << std::endl;
        std::cout << "Корректирует 1 ошибку, обнаруживает 2 ошибки" << std::endl;
    }

    // Кодирование данных
    std::vector<int> encode(const std::vector<int>& data) const {
        if (data.size() != m) {
            throw std::invalid_argument("Неверное количество информационных бит");
        }

        for (int bit : data) {
            if (bit != 0 && bit != 1) {
                throw std::invalid_argument("Данные должны состоять из 0 и 1");
            }
        }

        std::vector<int> codeword(n, 0);
        int dataIndex = 0;

        // Располагаем информационные биты в позициях, не являющихся степенями двойки
        for (int i = 1; i <= n; i++) {
            if (!isParityPosition(i)) {
                codeword[i-1] = data[dataIndex++];
            }
        }

        // Вычисляем проверочные биты
        for (int p = 0; p < r; p++) {
            int parityPos = std::pow(2, p) - 1; // Позиция проверочного бита (0-based)
            int parity = 0;

            // Вычисляем четность для битов, у которых в позиции p установлен 1
            for (int i = 1; i <= n; i++) {
                if (i & (1 << p)) {
                    if (i != (1 << p)) { // Исключаем сам проверочный бит
                        parity ^= codeword[i-1];
                    }
                }
            }

            codeword[parityPos] = parity;
        }

        return codeword;
    }

    // Декодирование с исправлением ошибок
    std::pair<std::vector<int>, int> decode(const std::vector<int>& received) const {
        if (received.size() != n) {
            throw std::invalid_argument("Неверная длина принятого слова");
        }

        for (int bit : received) {
            if (bit != 0 && bit != 1) {
                throw std::invalid_argument("Принятое слово должно состоять из 0 и 1");
            }
        }

        std::vector<int> syndrome(r, 0);

        // Вычисляем синдром
        for (int p = 0; p < r; p++) {
            int parity = 0;

            for (int i = 1; i <= n; i++) {
                if (i & (1 << p)) {
                    parity ^= received[i-1];
                }
            }

            syndrome[p] = parity;
        }

        // Определяем позицию ошибки
        int errorPosition = 0;
        for (int p = 0; p < r; p++) {
            if (syndrome[p] == 1) {
                errorPosition += std::pow(2, p);
            }
        }

        std::vector<int> corrected = received;

        // Исправляем ошибку, если она есть
        if (errorPosition > 0 && errorPosition <= n) {
            corrected[errorPosition - 1] ^= 1; // Инвертируем ошибочный бит
        }

        // Извлекаем информационные биты
        std::vector<int> decodedData;
        for (int i = 1; i <= n; i++) {
            if (!isParityPosition(i)) {
                decodedData.push_back(corrected[i-1]);
            }
        }

        return {decodedData, errorPosition};
    }

    // Внедрение ошибки в позиции pos (1-based)
    std::vector<int> introduceError(const std::vector<int>& codeword, int errorPos) const {
        if (codeword.size() != n) {
            throw std::invalid_argument("Неверная длина кодового слова");
        }

        if (errorPos < 1 || errorPos > n) {
            throw std::invalid_argument("Неверная позиция ошибки");
        }

        std::vector<int> corrupted = codeword;
        corrupted[errorPos - 1] ^= 1; // Инвертируем бит

        return corrupted;
    }

    // Кодирование строки
    std::vector<int> encodeString(const std::string& str) const {
        // Преобразуем строку в биты
        std::vector<int> data;
        for (char c : str) {
            std::bitset<8> bits(c);
            for (int i = 7; i >= 0; i--) {
                data.push_back(bits[i]);
            }
        }

        // Если данных больше, чем m, разбиваем на блоки
        std::vector<int> encoded;
        for (size_t i = 0; i < data.size(); i += m) {
            size_t blockSize = std::min((size_t)m, data.size() - i);
            std::vector<int> block(data.begin() + i, data.begin() + i + blockSize);

            // Дополняем блок нулями, если необходимо
            if (block.size() < m) {
                block.resize(m, 0);
            }

            auto encodedBlock = encode(block);
            encoded.insert(encoded.end(), encodedBlock.begin(), encodedBlock.end());
        }

        return encoded;
    }

    // Декодирование в строку
    std::string decodeToString(const std::vector<int>& encoded) const {
        if (encoded.size() % n != 0) {
            throw std::invalid_argument("Длина закодированных данных должна быть кратна " + std::to_string(n));
        }

        std::vector<int> decodedBits;
        int correctedErrors = 0;

        // Обрабатываем блоки
        for (size_t i = 0; i < encoded.size(); i += n) {
            std::vector<int> block(encoded.begin() + i, encoded.begin() + i + n);
            auto [decodedBlock, errorPos] = decode(block);

            if (errorPos > 0) {
                correctedErrors++;
            }

            decodedBits.insert(decodedBits.end(), decodedBlock.begin(), decodedBlock.end());
        }

        // Преобразуем биты в строку
        std::string result;
        for (size_t i = 0; i < decodedBits.size(); i += 8) {
            if (i + 8 <= decodedBits.size()) {
                char c = 0;
                for (int j = 0; j < 8; j++) {
                    c = (c << 1) | decodedBits[i + j];
                }
                result += c;
            }
        }

        return result;
    }

    // Проверка на одиночную ошибку
    bool hasSingleError(const std::vector<int>& received) const {
        if (received.size() != n) {
            return false;
        }

        int syndrome = 0;
        for (int p = 0; p < r; p++) {
            int parity = 0;
            for (int i = 1; i <= n; i++) {
                if (i & (1 << p)) {
                    parity ^= received[i-1];
                }
            }
            if (parity == 1) {
                syndrome |= (1 << p);
            }
        }

        return syndrome > 0;
    }

    // Проверка на двойную ошибку (обнаружение)
    bool hasDoubleError(const std::vector<int>& received) const {
        if (received.size() != n) {
            return false;
        }

        // Проверяем общую четность (дополнительный проверочный бит)
        int overallParity = 0;
        for (int bit : received) {
            overallParity ^= bit;
        }

        // Если есть синдром, но общая четность верна - это двойная ошибка
        return hasSingleError(received) && overallParity == 0;
    }

    // Вывод информации о коде
    void printCodeInfo() const {
        std::cout << "\n=== ИНФОРМАЦИЯ О КОДЕ ХЭММИНГА ===" << std::endl;
        std::cout << "Параметры: (" << n << ", " << m << ")" << std::endl;
        std::cout << "Избыточность: " << (double)r/n * 100 << "%" << std::endl;
        std::cout << "Скорость: " << (double)m/n << std::endl;
        std::cout << "Позиции проверочных бит: ";
        for (int i = 0; i < r; i++) {
            std::cout << (1 << i);
            if (i < r-1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // Визуализация размещения бит
    void printBitPositions() const {
        std::cout << "\nРазмещение бит в кодовом слове:" << std::endl;
        for (int i = 1; i <= n; i++) {
            std::cout << "Позиция " << i << ": ";
            if (isParityPosition(i)) {
                std::cout << "Проверочный бит P" << (int)std::log2(i) + 1;
            } else {
                std::cout << "Информационный бит D" << i - (int)std::log2(i) - 1;
            }
            std::cout << std::endl;
        }
    }

    // Геттеры
    int getDataBits() const { return m; }
    int getRedundantBits() const { return r; }
    int getTotalBits() const { return n; }
};


#endif //BMSTU_HAMMINGCODE_H