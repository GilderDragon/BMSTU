#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int a[8], b[8], c[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) scanf("%d", &a[i]);
    for (int i = 0; i < 8; i++) scanf("%d", &b[i]);
    bool flag = true;
    for (int i = 0; i < 8; i++) {
        bool flag1 = false;
        for (int j = 0; j < 8; j++) {
            if (a[i] == b[j] && c[j] != 1) {
                flag1 = true;
                c[j] = 1;
                break;
            }
        }
        if (!flag1) flag = false;
    }
    if (flag) printf("yes\n");
    else printf("no\n");

    return 0;
}
