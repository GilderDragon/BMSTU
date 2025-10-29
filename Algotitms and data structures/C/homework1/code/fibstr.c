#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fibstr(int n) {
    // Базовые случаи
    if (n == 1) {
        char *result = malloc(2 * sizeof(char));
        strcpy(result, "a");
        return result;
    }
    if (n == 2) {
        char *result = malloc(2 * sizeof(char));
        strcpy(result, "b");
        return result;
    }

    // Рекурсивно вычисляем две предыдущие строки
    char *prev2 = fibstr(n - 2);  // s_{n-2}
    char *prev1 = fibstr(n - 1);  // s_{n-1}

    // Вычисляем длину новой строки
    int total_len = strlen(prev1) + strlen(prev2);

    // Выделяем память для результата
    char *result = malloc((total_len + 1) * sizeof(char));

    // Конкатенируем строки: s_{n-2} + s_{n-1}
    strcpy(result, prev2);
    strcat(result, prev1);

    // Освобождаем память предыдущих строк
    free(prev2);
    free(prev1);

    return result;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("n must be positive integer\n");
        return 1;
    }

    char *fib_string = fibstr(n);
    printf("Fibonacci string s_%d: %s\n", n, fib_string);

    // Освобождаем память, как требуется по условию
    free(fib_string);

    return 0;
}