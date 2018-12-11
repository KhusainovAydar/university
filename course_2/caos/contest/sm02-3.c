//
// Created by MacBook on 06.12.2018.
//

#include <stdio.h>
#include <ctype.h>

int main() {
    int some_char;
    long long sum = 0;
    while ((some_char = getchar_unlocked()) != EOF) {
        if (isdigit(some_char)) {
            sum += (some_char - '0');
        }
    }
    printf("%lld\n", sum);
    return 0;
}