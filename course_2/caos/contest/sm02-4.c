//
// Created by MacBook on 06.12.2018.
//

#include <stdio.h>
#include <ctype.h>

int main() {
  int num[100];
  int c;
  while ((c = getchar()) != EOF) {
    if (isspace(c)) {
      continue;
    }
    long double ans = 0;
    int i = 0;
    num[0] = (c - '0');

    while (c != '.' && c != '\n' && c != EOF && c != ' ') {
      num[i] = (c - '0');
      ++i;
      c = getchar();
    }

    for (int j = 0; j != i; ++j) {
      if (j >= i - j - 1) {
        break;
      }
      int t = num[j];
      num[j] = num[i - j - 1];
      num[i - j - 1] = t;
    }

    long double step_seven = 1;
    for (int j = 0; j != i; ++j) {
      ans += step_seven * (num[j]);
      step_seven *= 7.0;
    }

    if (c == '.') {
      step_seven = 1;
      while ((c = getchar()) != ' ') {
        if (c == EOF || isspace(c)) {
          break;
        }
        step_seven /= 7.0;
        ans += step_seven * (c - '0');
      }
    }

    printf("%.10Lf\n", ans);

    if (c == EOF) {
      break;
    }
  }
}