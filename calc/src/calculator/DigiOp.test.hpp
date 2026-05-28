
#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/String.hpp"
#include <cstdio>

namespace DigiOpTest {

inline bool PushTest() {
  BEGIN_TEST
  DigiOpList list;
  const DigiOp el{123.456, Op::None};
  list.push(el);
  ASSERT_DBL(list.get(0).value, 123.456)
  list.push({222.22, Op::None});
  ASSERT_DBL(list.get(1).value, 222.22)
  return true;
}

inline bool SizeTest() {
  BEGIN_TEST
  DigiOpList list;
  const DigiOp el{123.456, Op::None};
  ASSERT_INT(list.size(), 0)
  list.push(el);
  ASSERT_INT(list.size(), 1)
  list.push(el);
  ASSERT_INT(list.size(), 2)
  return true;
}

inline bool EraseTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push({(double)i, Op::None});
  }
  ASSERT_INT(list.size(), 10);
  for (auto i = 0; i < 10; i++) {
    ASSERT_DBL(list.get(i).value, (double)i);
  }
  list.erase(0);
  ASSERT_INT(list.size(), 9);
  for (auto i = 0; i < list.size(); i++) {
    ASSERT_DBL(list.get(i).value, (double)i + 1);
  }
  return true;
}

inline bool GetTest() {
  BEGIN_TEST
  DigiOpList list;
  list.push({123, Op::None});
  ASSERT_DBL(list.get(0).value, 123.0)
  return true;
}

inline bool LimitsTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < MAX_DIGIOPLIST_SIZE; i++) {
    list.push({(double)i, Op::None});
  }
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  // Warning should print here
  list.push({123.123, Op::None});
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  return true;
}

inline bool ClearTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push({(double)i});
  }
  ASSERT_INT(list.size(), 10);
  list.clear();
  ASSERT_INT(list.size(), 0);
  return true;
}

inline bool LastTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push({(double)i});
  }

  ASSERT_DBL(list.last().value, 9.0);

  return true;
}

inline bool ToStringTest() {
  BEGIN_TEST
  DigiOpList list;
  list.push({1});
  list.push({0, Op::Add});
  list.push({2});
  list.push({0, Op::Subtract});
  list.push({3});
  list.push({0, Op::Multiply});
  list.push({4});
  list.push({0, Op::Divide});
  list.push({5});
  list.push({0, Op::ParenOpen});
  list.push({6});
  list.push({0, Op::ParenClose});

  char str[512] = {0};
  list.toString(str, 512);
  const char *expectedStr = "1 + 2 - 3 * 4 / 5 ( 6 )";
  ASSERT_INT(StrLen(str), StrLen(expectedStr));
  for (auto i = 0; i < StrLen(str); i++) {
    ASSERT_CHAR(str[i], expectedStr[i]);
  }

  return true;
}

inline bool All() {
  RUN_TEST(PushTest())
  RUN_TEST(GetTest())
  RUN_TEST(SizeTest())
  RUN_TEST(EraseTest())
  RUN_TEST(LimitsTest())
  RUN_TEST(ClearTest())
  RUN_TEST(ToStringTest())
  return true;
}

} // namespace DigiOpTest
