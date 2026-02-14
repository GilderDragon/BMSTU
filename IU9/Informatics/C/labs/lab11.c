#include <stdio.h>
#include <stdlib.h>

double** input_matrix(int n){
    double** arr = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) arr[i] = (double*)malloc(sizeof(double) * n);
    printf("Enter the matrix row by row:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &arr[i][j]);
        }
    }
    return arr;
}

void print_matrix(int n, double** arr){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) printf("%lf ", arr[i][j]);
        printf("\n");
    }
}

double sum_of_array(int n, double* arr){
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}

int main() {
    int n;
    printf("Enter the number of rows of the square matrix: ");
    scanf("%d", &n);
    while (n < 2){
        printf("The number of rows must be greater than 1");
        scanf("%d", &n);
    }
    
    double** arr = input_matrix(n);

    printf("You entered:\n");
    print_matrix(n, arr);
    
    double* main_diagonal = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) main_diagonal[i] = arr[i][i];
    
    double* secondary_diagonal = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) secondary_diagonal[i] = arr[n - i - 1][i];

    double main_diagonal_sum = sum_of_array(n, main_diagonal);
    double secondary_diagonal_sum = sum_of_array(n, secondary_diagonal);

    if (main_diagonal_sum > secondary_diagonal_sum) printf("The sum of the elements of the main diagonal "
                                                           "is greater than "
                                                           "the sum of the elements of the secondary diagonal");
    else if (main_diagonal_sum == secondary_diagonal_sum) printf("The sum of the elements of the main diagonal "
                                                                 "is equal to "
                                                                 "the sum of the elements of the secondary diagonal");
    else printf("The sum of the elements of the main diagonal "
                "is less than the sum of the elements of the secondary diagonal");
    
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
    free(main_diagonal);
    free(secondary_diagonal);
    
    return 0;
}
