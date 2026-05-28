#pragma once

#include "src/calculator/Calc.hpp"

#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"

#include <cstdio>

namespace CalculatorTest {

inline bool CalculateResultGood() {
  BEGIN_TEST

  DigiOpList input;
  input.push({12, Op::None});
  input.push({0, Op::Add});
  input.push({8, Op::None});

  const double result = Calc::CalculateResult(input);
  if (result != 20.0) {
    printf("CalculateResultGood. FAIL. Expected 20.0 got %f\n", result);
    return false;
  }

  return true;
}

}; // namespace CalculatorTest
