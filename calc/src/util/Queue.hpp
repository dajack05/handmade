#pragma once

#include <cstdio>

/*
 * Weird details...
 *
 * Instead of doing a linked-list or something smart like that, this queue works
 * by keeping a head and tail index.
 * When pushing a new element, if the head index is too large, it will slide
 * the whole data array down and reset the tail index to 0.
 *
 * While this might not be as time efficent, it only affects when the SIZE of
 * the array is approached. So for the uses I have it will likely never even get
 * hit.
 */

template <typename T, unsigned int SIZE> //
class Queue {
public:
  inline const void push(T value) {
    if (head >= SIZE && tail > 0) {
      squash();
    }
    if (head >= SIZE) {
      printf("Queue::push. Ran out of space. SIZE = %i\n", SIZE);
      return;
    }
    data[head++] = value;
  }

  inline const T pull() {
    if (size() < 0) {
      printf("Queue::pull. No items left in queue.\n");
      return {};
    }
    return data[tail++];
  }

  inline const unsigned int size() { return head - tail; }

  inline void squash() {
    const unsigned int diff = tail;
    printf("Queue::squash. Running squash %i. This should be infrequent...\n",
           diff);
    for (auto i = 0; i < head; i++) {
      data[i] = data[i + diff];
    }
    tail = 0;
    head = head - diff;
  }

private:
  T data[SIZE] = {};
  unsigned int head = 0;
  unsigned int tail = 0;
};
