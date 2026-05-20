#include "Calc.hpp"

namespace Calc {

double PerformInFix(double a, double b, Op op) {
  switch (op) {
  case Op::None:
    return a;
  case Op::Add:
    return a + b;
  case Op::Sub:
    return a - b;
  case Op::Mult:
    return a * b;
  case Op::Div:
    return a / b;
  }
}

} // namespace Calc
