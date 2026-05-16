#pragma once

#include <cstdio>
template <typename T, unsigned int SIZE> //
struct List {
  T data[SIZE];
  unsigned int writeIdx = 0;

  List() {}
  List(T initalizedValue) {
    for (auto i = 0; i < SIZE; i++) {
      data[i] = initalizedValue;
    }
  }

  unsigned int push(T item) {
    if (writeIdx >= SIZE) {
      printf("Cannot add to list. data is full.\n");
      return 0;
    }
    data[writeIdx++] = item;
    return writeIdx - 1;
  }

  unsigned int push_unique(T item) {
    for (auto i = 0; i < SIZE; i++) {
      if (data[i] == item) {
        return i;
      }
    }
    return push(item);
  }

  T pop() {
    T value = data[writeIdx - 1];
    writeIdx--;
    return value;
  }

  T &get(unsigned int index) {
    if (index >= SIZE) {
      printf("Attempted to get item beyond data size. Returning first item.\n");
      return data[0];
    }
    return data[index];
  }

  unsigned int count() { return writeIdx; }

  void clear() { writeIdx = 0; }

  T &last() { return data[writeIdx - 1]; }

  T &first() { return data[0]; }

  void copyFrom(const List<T, SIZE> &other) {
    for (unsigned int i = 0; i < SIZE; i++) {
      data[i] = other.data[i];
    }
    writeIdx = other.writeIdx;
  }
};
