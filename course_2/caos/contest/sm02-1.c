//
// Created by MacBook on 06.12.2018.
//

#include <stdio.h>

long long max(long long x, long long y) {
    return x > y ? x : y;
}


int main() {
    long long ans = 0;
    long long max_value = 0;
    long long cur_value = 0;
    while (scanf("%lld", &cur_value) == 1) {
        ans = max(ans, cur_value * max_value);
        max_value = max(max_value, cur_value);
    }
    printf("%lld\n", ans);
    return 0;
}