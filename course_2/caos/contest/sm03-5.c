//
// Created by MacBook on 08.12.2018.
//

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>

const uint32_t alp_size = 26;
const uint32_t digit_size = 10;
uint64_t stack[1007];

uint64_t add(uint64_t num, int digit) {
  char c = (char) digit;
  uint64_t value = 0;
  if (isdigit(digit)) {
    value += alp_size * 2 + '9' - c;
  } else if (isupper(digit)) {
    value += alp_size + 'Z' - c;
  } else if (islower(digit)) {
    value += 'z' - c;
  } else {
    assert(0);
  }

  return (num | (1uLL << value));
}

int operations(int i, int c) {
  if (c == '~') {
    stack[i] = ~stack[i];
    ++i;
  }
  if (c == '&') {
    stack[i - 1] &= stack[i];
  }
  if (c == '|') {
    stack[i - 1] |= stack[i];
  }
  if (c == '^') {
    stack[i - 1] ^= stack[i];
  }

  --i;
  return i;
}

int is_oper(int c) {
  if (c == '~' || c == '&' || c == '|' || c == '^') {
    return 1;
  }
  return 0;
}


int print(uint64_t ans, int i, int pos, int c) {
  while (i >= pos) {
    if (ans & (1uLL << i)) {
      putchar((char)(c - i));
    }
    --i;
  }
  return i;
}


int main() {
  int i = -1;
  int c;
  while ((c = getchar()) != EOF) {
    if (isspace(c)) {
      continue;
    }
    if (is_oper(c)) {
      i = operations(i, c);
      continue;
    }

    uint64_t push = 0;
    while (c != EOF && !isspace(c)) {
      push = add(push, c);
      c = getchar();
    }
    stack[++i] = push;

    if (c == EOF) {
      break;
    }
  }


  if (stack[0] == 0) {
    putchar('#');
    putchar('\n');
    return 0;
  }

  i = print(stack[0], 61, alp_size * 2, alp_size * 2 + digit_size - 1 + '0');
  i = print(stack[0], i, alp_size, alp_size * 2 - 1 + 'A');
  i = print(stack[0], i, 0, alp_size - 1 + 'a');
  putchar('\n');
  return 0;
}