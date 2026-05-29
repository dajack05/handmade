#include "src/calculator/Calc.hpp"

#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/Stack.hpp"

#include <cstdio>

namespace Calc {

DigiOpList prefixToPostfix(DigiOpList &input) {
  DigiOpList qu;
  Stack<DigiOp, MAX_DIGIOPLIST_SIZE> st;

  for (auto i = 0; i < input.size(); i++) {
    const DigiOp item = input.get(i);
    if (item.op == Op::None) {
      qu.push(item);
      continue;
    }

    // Is an operator

    if (item.op == Op::ParenOpen) {
      st.push(item);
      continue;
    }

    if (item.op == Op::ParenClose) {
      bool found = false;
      const auto size = st.size();
      for (auto i = size - 1; i >= 0; i--) {
        const DigiOp search = st.pop();
        if (search.op == Op::ParenOpen) {
          // Done with this set
          found = true;
          break;
        } else {
          qu.push(search);
        }
      }
      if (!found) {
        printf("Cal::prefixToPostfix. ERROR Failed to find '(' in stack.\n");
        return {};
      }
      continue;
    }

    const DigiOp topItem = st.pop();
    const unsigned int impNew = (unsigned int)item.op;
    const unsigned int impOld = (unsigned int)topItem.op;
    if (impOld > impNew) {
      // If the existing Op is higher importance, place it in the queue and
      // place the incoming Op on the stack.
      qu.push(topItem);
      st.push(item);
    } else {
      // If the existing Op is lower importance, place it back on the stack and
      // then place the new one on top.
      st.push(topItem);
      st.push(item);
    }
  }

  // Once finished, place any remaining Ops in the stack into the queue.

  for (auto i = 0; i < st.size(); i++) {
    qu.push(st.pop());
  }

  return qu;
}

double processPostfixed(DigiOpList &postfixedInput) {
  Stack<DigiOp, MAX_DIGIOPLIST_SIZE> st;

  for (auto i = 0; i < postfixedInput.size(); i++) {
    const DigiOp item = postfixedInput.get(i);
    if (item.op == Op::None) {
      st.push(item);
    } else {
      if (st.size() < 2) {
        printf("Cal::processPostfixed. ERROR. Malformed postfixedInput. Stack "
               "size is %i. Need minimum of 2.\n",
               st.size());
        return 0.0;
      }

      const double b = st.pop().value;
      const double a = st.pop().value;
      switch (item.op) {

      case Op::Add:
        st.push({a + b});
        break;
      case Op::Subtract:
        st.push({a - b});
        break;
      case Op::Multiply:
        st.push({a * b});
        break;
      case Op::Divide:
        st.push({a / b});
        break;
      case Op::None:
      case Op::ParenOpen:
      case Op::ParenClose:
        printf("Cal::processPostfixed. ERROR. Item is type %i... "
               "Invalid.\n",
               (unsigned int)item.op);
        return 0.0;
      }
    }
  }

  if (st.size() != 1) {
    printf("Cal::processPostfixed. ERROR. Stack has %i items instead of the "
           "expected 1 at end of process... Something went wrong.\n",
           st.size());
    return 0.0;
  }

  return st.pop().value;
}

double CalculateResult(DigiOpList &input) {
  DigiOpList prefixed = input;
  DigiOpList postfixed = prefixToPostfix(prefixed);
  return processPostfixed(postfixed);
}

bool InternalPostfixTest() {
  BEGIN_TEST
  DigiOpList input;
  input.push({0, Op::ParenOpen});
  input.push({5});
  input.push({0, Op::Multiply});
  input.push({4});
  input.push({0, Op::Add});
  input.push({3});
  input.push({0, Op::Multiply});
  input.push({2});
  input.push({0, Op::ParenClose});
  input.push({0, Op::Subtract});
  input.push({1});

  DigiOpList expected;
  expected.push({5});
  expected.push({4});
  expected.push({0, Op::Multiply});
  expected.push({3});
  expected.push({2});
  expected.push({0, Op::Multiply});
  expected.push({0, Op::Add});
  expected.push({1});
  expected.push({0, Op::Subtract});

  DigiOpList postfixed = prefixToPostfix(input);
  for (auto i = 0; i < expected.size(); i++) {
    ASSERT_DBL(postfixed.get(i).value, expected.get(i).value);
    ASSERT_INT(postfixed.get(i).op, expected.get(i).op);
  }

  return 1;
}

bool InternalPostfixProcessTest() {
  BEGIN_TEST
  DigiOpList expected;
  expected.pushAll({
      {5},
      {4},
      {Op::Multiply},
      {3},
      {2},
      {Op::Multiply},
      {Op::Add},
      {1},
      {Op::Subtract},
  });

  double result = processPostfixed(expected);
  ASSERT_DBL(result, 25.0);

  return true;
}

bool InternalPostfixSpecialTest() {
  BEGIN_TEST
  DigiOpList list;
  list.pushAll({
      {12},
      {Op::Multiply},
      {Op::ParenOpen},
      {3},
      {Op::Subtract},
      {10},
      {Op::ParenClose},
  });

  DigiOpList expect;
  expect.pushAll({
      {12},
      {3},
      {10},
      {Op::Subtract},
      {Op::Multiply},
  });

  DigiOpList result = prefixToPostfix(list);
  char resultStr[128] = {0};
  result.toString(resultStr, 128);
  printf("result: %s\n", resultStr);
  ASSERT_INT(result.size(), expect.size())

  for (auto i = 0; i < result.size(); i++) {
    const DigiOp digit = result.get(i);
    if (digit.isOp()) {
      ASSERT_INT((int)digit.op, (int)expect.get(i).op);
    } else {
      ASSERT_DBL(digit.value, expect.get(i).value);
    }
  }

  return true;
}

bool InternalTest() {
  RUN_TEST(InternalPostfixTest())
  RUN_TEST(InternalPostfixProcessTest())
  RUN_TEST(InternalPostfixSpecialTest())
  return true;
}

}; // namespace Calc
