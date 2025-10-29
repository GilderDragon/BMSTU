#include <stdio.h>

int strdiff(char *a, char *b) {
    int bit_pos = 0;
    
    // Проходим по всем символам строк
    while (*a != '\0' || *b != '\0') {
        // Если один из символов закончился, а другой нет
        if (*a == '\0' || *b == '\0') {
            // Сравниваем текущие символы побитово
            char char_a = (*a == '\0') ? 0 : *a;
            char char_b = (*b == '\0') ? 0 : *b;
            
            // Сравниваем биты текущих символов
            for (int i = 0; i < 8; i++) {
                if (((char_a >> i) & 1) != ((char_b >> i) & 1)) {
                    return bit_pos;
                }
                bit_pos++;
            }
            
            // Переходим к следующим символам
            if (*a != '\0') a++;
            if (*b != '\0') b++;
            continue;
        }
        
        // Сравниваем биты текущих символов
        for (int i = 0; i < 8; i++) {
            if (((*a >> i) & 1) != ((*b >> i) & 1)) {
                return bit_pos;
            }
            bit_pos++;
        }
        
        // Переходим к следующим символам
        a++;
        b++;
    }
    
    // Если дошли до конца и все биты совпали
    return -1;
}

int main() {
    // Тестовые примеры
    char str1[] = "aa";
    char str2[] = "ai";
    
    int result = strdiff(str1, str2);
    printf("Strings: '%s' and '%s'\n", str1, str2);
    printf("First differing bit: %d\n", result);
    
    // Тест с равными строками
    char str3[] = "hello";
    char str4[] = "hello";
    
    result = strdiff(str3, str4);
    printf("\nStrings: '%s' and '%s'\n", str3, str4);
    printf("First differing bit: %d\n", result);
    
    // Тест с разной длиной
    char str5[] = "abc";
    char str6[] = "ab";
    
    result = strdiff(str5, str6);
    printf("\nStrings: '%s' and '%s'\n", str5, str6);
    printf("First differing bit: %d\n", result);
    
    return 0;
}