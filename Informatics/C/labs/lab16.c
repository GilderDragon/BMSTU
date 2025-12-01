#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void input_array(double* arr, const int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
}


void generate_array(double* arr, const int n) {
    const double RANGE = 1000000.0;

    for (int i = 0; i < n; i++) {
        arr[i] = (2.0 * rand() / RAND_MAX - 1.0) * RANGE;
    }
}


void create_array(double* arr, const int n) {
    printf("Choose one option:\n");
    printf("1) Input array by yourself\n");
    printf("2) Generate array\n");

    int choice;
    scanf("%d", &choice);

    (choice == 1) ? input_array(arr, n) : generate_array(arr, n);
}


void print_array(double* arr, const int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}


void print_array_select(double* arr, const int n) {
    int choice;
    printf("Choose one option:\n1)Print array\n2)Do nothing\n");
    scanf("%d", &choice);

    if (choice == 1) print_array(arr, n);
}


void bubble_sort(double* arr, const int n) {
    double temp;
    bool flag;
    for (int i = 0; i < n; i++) {
        flag = false;
        for (int j = n - 2; j > -1; j--) {
            if (arr[j] > arr[j + 1]) {
                flag = true;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (!flag) break;
    }
}


int compare(const void* a, const void* b) {
    if (*(double*)a < *(double*)b) return -1;
    if (*(double*)a > *(double*)b) return 1;
    return 0;
}


int main() {
    int n;
    do {
        printf("Input number of elements: ");
        scanf("%d", &n);
    } while (n < 1);

    double* arr1 = (double*)malloc(sizeof(double) * n);
    double* arr2 = (double*)malloc(sizeof(double) * n);

    srand(time(NULL));

    create_array(arr1, n);

    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i];
    }

    print_array_select(arr1, n);

    printf("Bubble sort: ");
    clock_t start = clock();
    bubble_sort(arr1, n);
    printf("%lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    printf("qsort: ");
    start = clock();
    qsort(arr2, n, sizeof(double), compare);
    printf("%lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    print_array_select(arr1, n);

    free(arr1);
    free(arr2);

    return 0;
}

