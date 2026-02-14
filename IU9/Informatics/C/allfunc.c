#include <stdio.h>
#include <stdlib.h>

void input_arr(int n, int** arr){ //lab10
    *arr = (int*)malloc(sizeof(int) * n);
    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &(*arr)[i]);
}

void print_arr(int n, int* arr){ //lab10
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int sum_of_digits(int n){ //lab10
    n = (n > 0) ? n : -n;
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

double sum_of_array(int n, double* arr){ //lab11
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}

void input_matrix(int** arr, int m, int n) { //lab13
    printf("Input matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void print_matrix(int** arr, int m, int n) { //lab13
    printf("Matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void read_matrix(FILE* file, double** arr, int m) { //lab14
    for (int i = 0; i < m; i++) {
        fscanf(file, "%lf %lf %lf", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
}

int min(double* arr, int n) { //returns index
    int mini = 0;
    for (int i = 1; i < n; i++) {
        if (arr[mini] > arr[i]) mini = i;
    }
    return mini;
}

int max(double* arr, int n) { //returns index
    int maxi = 0;
    for (int i = 1; i < n; i++) {
        if (arr[maxi] < arr[i]) maxi = i;
    }
    return maxi;
}
