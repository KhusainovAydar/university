//
// Created by MacBook on 06.12.2018.
//

#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int main() {
  unsigned int some_trash, ans;
  while ((scanf("%x", &some_trash)) != EOF) {
    ans = 0;
    int cnt = 0;
    for (int i = 0; i != 4; ++i) {
      ans = 0;
      unsigned int some_byte;
      while (cnt != 4 && (scanf("%x", &some_byte)) != EOF) {
        ++cnt;
        unsigned int to_byte = CHAR_BIT * sizeof(unsigned int) - CHAR_BIT * cnt;
        ans |= (some_byte << to_byte);
      }

      if (cnt == 4) {
        cnt = 0;
        printf("%u\n", ans);
      }
    }
  }
}