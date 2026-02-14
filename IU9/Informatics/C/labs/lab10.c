#include <stdio.h>
#include <stdlib.h>

void input_arr(int n, int** arr){
    *arr = (int*)malloc(sizeof(int) * n);
    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &(*arr)[i]);
}

void print_arr(int n, int* arr){
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

int max_sum_digits_elem(int n, int* arr){
    int max = 0, maxi = -1, sum;
    for (int i = 0; i < n; i++){
        sum = sum_of_digits(arr[i]);
        if (sum > max){
            max = sum;
            maxi = i;
        }
    }
    return maxi;
}

int main() {
    int n;
    printf("Enter the number of array elements: ");
    scanf("%d", &n);
    while (n < 1){
        printf("The number of elements must be greater than 0: ");
        scanf("%d", &n);
    }

    int* arr;
    input_arr(n, &arr);

    printf("You entered ");
    print_arr(n, arr);

    printf("The element with the highest sum of digits is in %d place", max_sum_digits_elem(n, arr));

    free(arr);

    return 0;
}
