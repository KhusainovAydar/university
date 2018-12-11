//
// Created by MacBook on 06.12.2018.
//

#include <inttypes.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t sum;
    uint32_t maximum = (uint32_t) ~0;
    maximum >>= 1;
    if (__builtin_add_overflow(v1, v2, &sum)) {
        if (v1 > 0) {
            return (int32_t) maximum;
        } else {
            return -(int32_t) maximum - 1;
        }
    } else {
        return v1 + v2;
    }
}