#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x;
    scanf("%d", &x);
    x = abs(x);
    int *arr = malloc(sizeof(int) * (x + 1));
    for (int i = 1; i <= x; i++) arr[i] = i;
    for (int i = 2; i * i <= x; i++) {
        for (int j = i * i; j <= x; j++) {
            if (arr[j] % i == 0) arr[j] = 0;
        }
    }
    for (int i = x; i > 1; i--) {
        if (arr[i] != 0 && x % arr[i] == 0) {
            printf("%d", arr[i]);
            break;
        }
    }

    return 0;
}
