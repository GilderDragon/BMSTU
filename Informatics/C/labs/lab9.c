#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%i%i", &m, &n);
    while (m < 2 || n < 2){
        printf("The numbers entered cannot be less than 2, please re-enter: ");
        scanf("%i%i", &m, &n);
    }

    double** arr = (double**)malloc(sizeof(double*) * m);

    for (int i = 0; i < m; i++) arr[i] = (double*)malloc(sizeof(double) * n);

    printf("Enter the matrix elements row by row:\n");
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) scanf("%lf", &arr[i][j]);

    int max = 0, maxi = -1, count;

    for (int j = 0; j < n; j++){
        count = 0;
        for (int i = 0; i < m; i++){
            if (arr[i][j] == 0) count++;
        }
        if (count > max){
            max = count;
            maxi = j;
        }
    }

    if (maxi == -1) printf("The matrix does not have columns containing zero elements");
    else printf("The column with the maximum number of zero elements has index %i", maxi);

    for (int i = 0; i < m; i++) free(arr[i]);
    free(arr);

    return 0;
}
