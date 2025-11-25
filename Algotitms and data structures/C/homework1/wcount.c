#include <stdio.h>
#include <string.h>

int wcount(char *s)
{
    int count = 0;
    int in_word = 0; // Флаг, указывающий, находимся ли мы внутри слова

    // Проходим по каждому символу строки
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            // Если текущий символ не пробел и мы не внутри слова,
            // значит начинается новое слово
            if (!in_word) {
                count++;
                in_word = 1; // Устанавливаем флаг, что мы внутри слова
            }
        } else {
            // Если встретили пробел, сбрасываем флаг
            in_word = 0;
        }
    }

    return count;
}

int main()
{
    char input_string[1000];

    printf("Enter a string: ");
    fgets(input_string, sizeof(input_string), stdin);

    // Удаляем символ новой строки, если он есть
    size_t len = strlen(input_string);
    if (len > 0 && input_string[len - 1] == '\n') {
        input_string[len - 1] = '\0';
    }

    int word_count = wcount(input_string);
    printf("Number of words: %d\n", word_count);

    return 0;
}