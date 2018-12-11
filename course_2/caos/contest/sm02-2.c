//
// Created by MacBook on 06.12.2018.
//

#include <stdio.h>

int main() {
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);

    for (int i = 0; i != n; ++i) {
        putchar(' ');
    }

    for (int i = a; i != b; ++i) {
        printf(" %*d", n, i);
    }
    putchar('\n');

    for (long long i = a; i != b; ++i) {
        printf("%*lld", n, i);
        for (long long j = a; j != b; ++j) {
            printf(" %*lld", n, i * j);
        }
        putchar('\n');
    }
    return 0;
}