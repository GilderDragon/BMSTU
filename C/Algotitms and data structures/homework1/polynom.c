#include <stdio.h>
#include <stdlib.h>

void add(int **arr, int *size, int a) {
    *arr = realloc(*arr, (*size + 1) * sizeof(int));
    (*arr)[*size] = a;
    (*size)++;
}

void derivative(int arr[], int size) {
    for (int i = 0; i < size; i++) arr[i] = arr[i] * i;
}

int solve(int arr[], int x0, int n, int i) {
    if (i == n) return arr[i];
    return arr[i] + solve(arr, x0, n, i + 1) * x0;
}

int main(void) {
    int n, x0;
    scanf("%d %d", &n, &x0);
    int *arr = NULL; // начало со свободного члена
    int a, size = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        add(&arr, &size, a);
    }

    printf("%d\n", solve(arr, x0, n - 1, 0));

    derivative(arr, n);
    arr++;

    printf("%d\n", solve(arr, x0, n - 2, 0));

    free(arr);
    return 0;
}