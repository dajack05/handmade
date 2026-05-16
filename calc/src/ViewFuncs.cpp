#include "src/ViewFuncs.hpp"

#include "src/View.hpp"
#include <cstdio>
#include <raylib.h>

namespace ViewFuncs {
void RenderView(const View &view) {
  const Rectangle rect = {
      (float)view.x,
      (float)view.y,
      (float)view.w,
      (float)view.h,
  };
  DrawRectangleRounded(rect, view.roundness, 4, view.bgColor);
  if (view.borderThickness > 0) {
    DrawRectangleRoundedLinesEx(rect, view.roundness, 4, view.borderThickness,
                                view.borderColor);
  }
}

void RenderButton(const View &view) {
  View nView = view;
  if (view.state == ViewState::Hover || view.state == ViewState::Active) {
    nView.borderThickness = 2;
  }
  if (view.state == ViewState::Active && view.onClickFunc) {
    view.onClickFunc();
  }
  RenderView(nView);
}
} // namespace ViewFuncs
