#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int solve(int arr[], int a, int n, int i) {
    if (i == n) return a * arr[i];
    return a * arr[i] + solve(arr, a, n, i + 1) * 2;
}

int main(void) {
    int a, b, m;
    scanf("%d %d %d", &a, &b, &m);
    int size = log2(b) + 1;
    int *bin_b = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        bin_b[i] = b % 2;
        b /= 2;
    }

    printf("%d\n", solve(bin_b, a, size - 1, 0) % m);

    free(bin_b);
    return 0;
}
