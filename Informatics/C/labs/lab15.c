#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void input_array(double* arr, const int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
}


void generate_array(double* arr, const int n) {
    srand(time(NULL));

    const double min = -(1<<30), max = 1<<31;

    for (int i = 0; i < n; i++) {
        arr[i] = min + (max - min) * ((double)rand() / RAND_MAX);
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


int min(double* arr, const int n) {
    int min = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min]){
            min = i;
        }
    }
    return min;
}


void sort(double* arr, const int n) {
    double temp;
    for (int i = 0; i < n; i++) {
        int mini = min(&arr[i], n - i) + i;
        if (i != mini) {
            temp = arr[i];
            arr[i] = arr[mini];
            arr[mini] = temp;
        }
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


    create_array(arr1, n);

    print_array_select(arr1, n);

    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i];
    }

    printf("Selection sort: ");
    clock_t start = clock();
    sort(arr1, n);
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
