#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Solution {
    int number_of_solutions;
    double x1;
    double x2;
};


struct Solution solve_linear_equation(double k, double b) {
    struct Solution answer;
    if (k == 0) {
        if (b == 0) {
            answer.number_of_solutions = -1;
        } else {
            answer.number_of_solutions = 0;
        }
    } else {
        answer.number_of_solutions = 1;
        answer.x1 = -b / k;
    }
    return answer;
}


struct Solution solve_quadratic_equation(double a, double b, double c) {
    struct Solution answer;
    double d;
    d = b * b - 4 * a * c;
    if (d > 0) {
        d = sqrt(d);
        answer.number_of_solutions = 2;
        answer.x1 = (-b + d) / (2 * a);
        answer.x2 = (-b - d) / (2 * a);
    } else if (d == 0) {
        answer.number_of_solutions = 1;
        answer.x1 = -b / (2 * a);
    } else {
        answer.number_of_solutions = 0;
    }
    return answer;
}


void read_matrix(FILE* file, double** arr, int m) {
    for (int i = 0; i < m; i++) {
        fscanf(file, "%lf %lf %lf", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
}


int main() {
    const char path[] = "lab14.txt";
    FILE* file = fopen(path, "r");

    const int n = 3, m;

    fscanf(file, "%d", &m);

    double** arr = (double**)malloc(sizeof(double*) * m);
    for (int i = 0; i < m; i++) arr[i] = (double*)malloc(sizeof(double) * n);

    read_matrix(file, arr, m);
    fclose(file);

    for (int i = 0; i < m; i++) {
        printf("\nFor a = %lf, b = %lf, c = %lf\n", arr[i][0], arr[i][1], arr[i][2]);
        if (arr[i][0] == 0.0) {
            printf("Solution of the equation %lfx + %lf = 0\n", arr[i][1], arr[i][2]);
            struct Solution solution = solve_linear_equation(arr[i][1], arr[i][2]);
            if (solution.number_of_solutions == -1) {
                printf("X - any number\n");
            } else if (solution.number_of_solutions == 0){
                printf("No real solutions\n");
            } else {
                printf("X = %lf\n", solution.x1);
            }
        } else {
            printf("Solution of the equation %lfx^2 + %lfx + %lf = 0\n", arr[i][0], arr[i][1], arr[i][2]);
            struct Solution solution = solve_quadratic_equation(arr[i][0], arr[i][1], arr[i][2]);
            if (solution.number_of_solutions == 0) {
                printf("No real solutions\n");
            } else if (solution.number_of_solutions == 1) {
                printf("X = %lf\n", solution.x1);
            } else {
                printf("X1 = %lf, X2 = %lf\n", solution.x1, solution.x2);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
