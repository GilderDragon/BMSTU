#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int size, k, s = 0, max_s = 0;
    scanf("%d %d", &size, &k);
    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) scanf("%d", &arr[i]);
    for (int i = 0; i < size; i++) {
        if (i < k) s += arr[i];
        else {
            s += arr[i];
            s -= arr[i - k];
        }
        max_s = max_s > s ? max_s : s;
    }
    printf("%d\n", max_s);

    return 0;
}
