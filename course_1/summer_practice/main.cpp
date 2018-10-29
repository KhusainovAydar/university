#include <iostream>
#include "scope_guard.h"

void kek() {
  auto memes = SG::setScopeGuardOnFail([]{ std::cout << "FAIL" << '\n'; });
  std::cout << "first" << '\n';
  throw 1;
}

int main() {
  try {
    kek();
  } catch(...) {
    std::cout << "THE END" << '\n';
  }
  return 0;
}