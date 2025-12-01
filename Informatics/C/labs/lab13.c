#include <stdio.h>
#include <stdlib.h>


struct Pair {
    int count;
    int m;
    int n;
};


void input_matrix(int** arr, int m, int n) {
    printf("Input matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}


void print_matrix(int** arr, int m, int n) {
    printf("Matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}


int count_min_digit(int number) {
    int digit, min_digit = number % 10, count = 1, max_count = 1;
    number /= 10;
    while (number > 0) {
        digit = number % 10;
        number /= 10;

        if (digit < min_digit) {
            min_digit = digit;
            count = max_count = 1;
        } else if (digit == min_digit) {
            count += 1;
            if (count > max_count) {
                max_count = count;
            }
        }
    }
    return max_count;
}


struct Pair find_max_num_min_digit(int** arr, int m, int n) {
    struct Pair index;
    int max_count = 0, temp;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp = count_min_digit(arr[i][j]);
            if (temp > max_count) {
                max_count = temp;
                index.count = max_count;
                index.m = i;
                index.n = j;
            }
        }
    }
    return index;
}


int main() {
    int m, n;
    do {
        printf("Input m and n: ");
        scanf("%d%d", &m, &n);
    }
    while (m < 2 || n < 2);

    int** arr = (int**)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++) arr[i] = (int*)malloc(sizeof(int) * n);

    input_matrix(arr, m, n);

    print_matrix(arr, m, n);

    struct Pair answer = find_max_num_min_digit(arr, m, n);

    if (answer.count == 1) {
        printf("No repeating numbers");
    } else {
        printf("Answer: %d %d", answer.m, answer.n);
    }

    for (int i = 0; i < m; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}