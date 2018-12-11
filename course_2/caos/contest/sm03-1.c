//
// Created by MacBook on 06.12.2018.
//

#include <inttypes.h>

uint32_t max(uint32_t x, uint32_t y) {
    return x > y ? x : y;
}

uint32_t satsum(uint32_t v1, uint32_t v2) {
    uint32_t sum = v1 + v2;
    if (sum >= max(v1, v2)) {
        return sum;
    } else {
        return (uint32_t) ~0;
    }
}