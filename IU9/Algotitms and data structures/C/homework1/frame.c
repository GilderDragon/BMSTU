#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(const char *message) {
    fprintf(stderr, "%s\n", message);
}

void print_usage() {
    printf("Usage: frame <height> <width> <text>\n");
}

int main() {
    int height, width;
    char text[1000];

    // Ввод параметров во время выполнения
    printf("Enter height: ");
    if (scanf("%d", &height) != 1) {
        print_error("Invalid height input");
        return 1;
    }

    printf("Enter width: ");
    if (scanf("%d", &width) != 1) {
        print_error("Invalid width input");
        return 1;
    }

    printf("Enter text: ");
    getchar(); // Считываем оставшийся символ новой строки
    if (fgets(text, sizeof(text), stdin) == NULL) {
        print_error("Invalid text input");
        return 1;
    }

    // Удаляем символ новой строки из текста
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    int text_len = strlen(text);

    // Проверка возможности размещения текста
    if (height < 3 || width < text_len + 2) {
        print_error("Error");
        return 1;
    }

    // Вычисление позиции текста
    int vertical_padding = (height - 3) / 2;  // Пробелы сверху до текста
    int horizontal_padding = (width - text_len - 2) / 2;  // Пробелы слева от текста

    // Верхняя граница рамки
    for (int i = 0; i < width; i++) {
        printf("*");
    }
    printf("\n");

    // Пустые строки сверху
    for (int i = 0; i < vertical_padding; i++) {
        printf("*");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("*\n");
    }

    // Строка с текстом
    printf("*");
    for (int i = 0; i < horizontal_padding; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (int i = 0; i < width - text_len - horizontal_padding - 2; i++) {
        printf(" ");
    }
    printf("*\n");

    // Пустые строки снизу
    for (int i = 0; i < height - vertical_padding - 3; i++) {
        printf("*");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("*\n");
    }

    // Нижняя граница рамки
    for (int i = 0; i < width; i++) {
        printf("*");
    }
    printf("\n");

    return 0;
}