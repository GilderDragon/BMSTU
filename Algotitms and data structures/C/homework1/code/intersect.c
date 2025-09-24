#include <stdio.h>
#include <math.h>

int main(void) {
    int size_a, size_b;
    scanf("%d %d", &size_a, &size_b);
    int a = 0, b = 0;
    int temp;
    for (int i = 0; i < size_a; i++) {
        scanf("%d", &temp);
        a = a | (int) pow(2, temp);
    }
    for (int i = 0; i < size_b; i++) {
        scanf("%d", &temp);
        b = b | (int) pow(2, temp);
    }
    int mul = a & b;
    int m = (int) log2(mul) + 1;

    for (int i = 0; i < m; i++) {
        if (mul & (1 << i)) printf("%d ", i);
    }

    return 0;
}
