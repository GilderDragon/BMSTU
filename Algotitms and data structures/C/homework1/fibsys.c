#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num;
    scanf("%d",&num);
    int *arr = malloc(sizeof(int) * 2);
    arr[0] = 1;
    arr[1] = 1;
    int size = 2;
    while (arr[size - 1] + arr[size - 2] < num) {
        size += 1;
        arr = realloc(arr, sizeof(int) * size);
        arr[size - 1] = arr[size - 2] + arr[size - 3];
    }

    for (int i = size - 1; i > 0; i--) {
        if (arr[i] <= num) {
            printf("%d", 1);
            num -= arr[i];
        } else printf("%d", 0);
    }

    free(arr);
    return 0;
}
