#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void input_arr(int n, int* arr){
    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
}

void print_arr(int n, int* arr){
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int sum_of_digits(int n){
    n = (n > 0) ? n : -n;
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    int n;
    do {
        printf("Enter length of array: ");
        scanf("%d", &n);
    } while (n < 5);

    int* arr = (int*)malloc(n * sizeof(int));

    input_arr(n, arr);

    print_arr(n, arr);

    bool flag = false;
    for (int i = n / 5; i < 3 * n / 5; i++) {
        if (sum_of_digits(arr[i]) < 11) {
            printf("%d ", arr[i]);
            flag = true;
        }
    }

    if (!flag) {
        printf("No suitable numbers");
    }

    free(arr);

    return 0;
}
