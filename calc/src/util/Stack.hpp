#pragma once

#include <cstdio>
template <typename T, unsigned int SIZE> //
class Stack {
public:
  inline const void push(T value) {
    if (writeIdx >= SIZE) {
      printf("Stack::push. Ran out of space. SIZE = %i\n", SIZE);
      return;
    }
    data[writeIdx++] = value;
  }

  inline const T pop() {
    if (writeIdx < 1) {
      printf("Stack::pop. No items left in stack.\n");
      return {};
    }
    return data[--writeIdx];
  }

  inline const unsigned int size() { return writeIdx; }

private:
  T data[SIZE] = {};
  unsigned int writeIdx = 0;
};
