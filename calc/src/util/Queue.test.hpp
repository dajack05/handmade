#include "src/tests/TestMacros.hpp"
#include "src/util/Queue.hpp"
#include <cstdio>

namespace QueueTest {

inline bool PushTest() {
  BEGIN_TEST
  Queue<int, 10> queue;
  queue.push(1);
  ASSERT_INT(queue.size(), 1)
  queue.push(2);
  ASSERT_INT(queue.size(), 2)
  return true;
}

inline bool PullTest() {
  BEGIN_TEST
  Queue<int, 10> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  ASSERT_INT(queue.size(), 3)

  ASSERT_INT(queue.pull(), 1)
  ASSERT_INT(queue.size(), 2)

  ASSERT_INT(queue.pull(), 2)
  ASSERT_INT(queue.size(), 1)

  ASSERT_INT(queue.pull(), 3)
  ASSERT_INT(queue.size(), 0)
  return true;
}

inline bool LimitsTest() {
  BEGIN_TEST
  const unsigned int testQueueSize = 10;
  Queue<int, testQueueSize> queue;
  for (auto i = 0; i < testQueueSize; i++) {
    queue.push(i);
  }
  ASSERT_INT(queue.size(), testQueueSize);

  // Warning should print here
  queue.push(123);
  ASSERT_INT(queue.size(), testQueueSize);

  return true;
}

inline bool DefragmentTest() {
  BEGIN_TEST
  const unsigned int testQueueSize = 10;
  Queue<int, testQueueSize> queue;
  for (auto i = 0; i < testQueueSize; i++) {
    queue.push(i);
  }
  ASSERT_INT(queue.size(), testQueueSize);

  queue.pull();
  queue.pull();
  queue.pull();

  ASSERT_INT(queue.size(), testQueueSize - 3);

  queue.push(123);
  queue.push(123);
  queue.push(123);

  ASSERT_INT(queue.size(), testQueueSize);

  return true;
}

inline bool All() {
  RUN_TEST(PushTest())
  RUN_TEST(PullTest())
  RUN_TEST(LimitsTest())
  RUN_TEST(DefragmentTest())
  return true;
}

}; // namespace QueueTest
