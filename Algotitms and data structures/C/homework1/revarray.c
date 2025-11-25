#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void revarray(void *base, unsigned long nel, unsigned long width) {
    void *temp = malloc(nel * width);
    memcpy(temp, base, nel * width);
    for (int i = 0; i < nel; i++) {
        memcpy(base + (nel - i - 1) * width, temp + width * i, width);
    }
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    revarray(arr, 5, 4);
    for (int i = 0; i < 5; i++) {printf("%d ", arr[i]);}
    printf("\n");
    char arr2[5] = {'a', 'b', 'c', 'd', 'e'};
    revarray(arr2, 5, 1);
    for (int i = 0; i < 5; i++) {printf("%c", arr2[i]);}
    return 0;
}
