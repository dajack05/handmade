#pragma once

#include <cstdio>
#include <type_traits>

template <typename T, unsigned int SIZE> //
struct RingBuffer {
  T data[SIZE];
  unsigned int writeIdx = 0;

  RingBuffer() {}

  unsigned int push(const T item) {
    data[writeIdx++] = item;
    if (writeIdx >= SIZE) {
      writeIdx = 0;
    }
  }

  T &getNext() {
    unsigned int idx = writeIdx++;
    if (writeIdx >= SIZE) {
      writeIdx = 0;
    }
    if (std::is_array<T>::value) {
      const unsigned int array_len = sizeof(data[0]) / sizeof(data[0][0]);
      for (auto i = 0; i < array_len; i++) {
        data[idx][i] = {};
      }
    }
    return data[idx];
  }

  T &get(unsigned int index) {
    if (index >= SIZE) {
      printf("RingBuffer. Attempted to read position %i out of max size %i\n",
             index, SIZE);
      return data[0];
    }
    return data[index];
  }

  unsigned int latestIndex() {
    if (writeIdx > 0) {
      return writeIdx - 1;
    }
    return SIZE - 1;
  }
};
