#pragma once

namespace Calc {

enum class Op {
  None,
  Add,
  Sub,
  Mult,
  Div,
};

double PerformInFix(double a, double b, Op op);
} // namespace Calc
