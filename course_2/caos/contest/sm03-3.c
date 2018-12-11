//
// Created by MacBook on 06.12.2018.
//

int bitcount(STYPE value) {
    int cnt = 0;
    UTYPE copy_value = value;
    while (copy_value > 0) {
        if (copy_value & 1) {
            ++cnt;
        }
        copy_value >>= 1;
    }
    return cnt;
}