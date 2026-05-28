#include "src/calculator/Calculator.hpp"
#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/Stack.hpp"
#include <cstdio>

namespace Cal {

DigiOpList prefixToPostfix(const DigiOpList &input) {
  DigiOpList qu;
  Stack<DigiOp, MAX_DIGIOPLIST_SIZE> st;

  for (auto i = 0; i < input.size(); i++) {
    const DigiOp item = input.get(i);
    if (item.op == Op::None) {
      qu.push(item);
      continue;
    }

    // Is an operator
    if (st.size() == 0) {
      st.push(item);
      continue;
    }

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

double CalculateResult(const DigiOpList &input) {
  const DigiOpList postfixed = prefixToPostfix(input);

  return 0.0;
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

  const DigiOpList postfixed = prefixToPostfix(input);
  for (auto i = 0; i < expected.size(); i++) {
    ASSERT_DBL(postfixed.get(i).value, expected.get(i).value);
    ASSERT_INT(postfixed.get(i).op, expected.get(i).op);
  }

  return 1;
}

bool InternalTest() {
  RUN_TEST(InternalPostfixTest())
  return true;
}

}; // namespace Cal
