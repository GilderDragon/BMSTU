#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int row, col;
    scanf("%d %d", &row, &col);
    const int int_max = INT_MAX;

    int **row_max = malloc(sizeof(int) * row * 2);
    for (int i = 0; i < row; i++) row_max[i] = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < row; i++) row_max[i][0] = -int_max;

    int **col_min = malloc(sizeof(int) * col * 2);
    for (int i = 0; i < col; i++) col_min[i] = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < col; i++) col_min[i][0] = int_max;

    int temp;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &temp);
            if (temp > row_max[i][0]) {
                row_max[i][0] = temp;
                row_max[i][1] = j;
            }
            if (temp < col_min[j][0]) {
                col_min[j][0] = temp;
                col_min[j][1] = i;
            }
        }
    }

    bool flag = true;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (row_max[i][1] == j && col_min[j][1] == i) {
                printf("%d %d\n", i, j);
                flag = false;
            }
        }
    }

    if (flag) printf("none\n");

    return 0;
}