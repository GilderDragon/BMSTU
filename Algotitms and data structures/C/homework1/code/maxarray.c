#include <stdio.h>
#include <stdlib.h>

int maxarray(void *base, unsigned long nel, unsigned long width) {
    char *ptr = base;
    unsigned char *max = calloc(width, 1);
    int imax = -1;
    for (int i = 0; i < nel; i++) {
        for (int j = 0; j < width; j++) {
            if (*ptr > max[j]) {
                imax = i;
                for (int k = j; k < width; k++) {
                    max[k] = *ptr;
                    ptr++;
                }
                break;
            } else ptr++;
        }
    }
    return imax;
}


int main(void) {
    int a[] = {1, 4, 2, 3, 1023};
    printf("%d\n", maxarray(a, sizeof(a) / sizeof(a[0]), sizeof(a[0])));

    char b[] = "afdce";
    printf("%d\n", maxarray(b, sizeof(b) / sizeof(b[0]), sizeof(b[0])));

    short int c[] = {3, 5, 9, 6, 7, 2, 1};
    printf("%d\n", maxarray(c, sizeof(c) / sizeof(c[0]), sizeof(c[0])));

    return 0;
}
