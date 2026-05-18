#include "src/ViewFuncs.hpp"

#include "src/View.hpp"
#include "src/util/String.hpp"
#include <raylib.h>

namespace ViewFuncs {
void RenderView(const View &view) {
  const Rectangle rect = {
      (float)view.x,
      (float)view.y,
      (float)view.w,
      (float)view.h,
  };
  if (view.bgColor.a != 0) {
    DrawRectangleRounded(rect, view.roundness, 8, view.bgColor);
  }
  if (view.borderThickness > 0) {
    DrawRectangleRoundedLinesEx(rect, view.roundness, 8, view.borderThickness,
                                view.borderColor);
  }
}

void RenderButton(const View &view) {
  View nView = view;
  if (view.state == ViewState::Hover || view.state == ViewState::Active) {
    nView.borderThickness = 4;
  }
  if (view.state == ViewState::Active && view.onClickFunc) {
    view.onClickFunc(view);
  }
  RenderView(nView);
  if (StrLen(view.label) > 0) {
    const int fontSize = view.h / 2;
    const int textWidth = MeasureText(view.label, fontSize);
    const int center_x = view.x + view.w / 2;
    const int center_y = view.y + view.h / 2;
    DrawText(view.label, center_x - textWidth / 2, center_y - fontSize / 2,
             view.h / 2, view.textColor);
  }
}

void RenderText(const View &view) {
  View nView = view;
  RenderView(view);
  if (StrLen(view.label) > 0) {
    const int fontSize = view.h / 2;
    const int textWidth = MeasureText(view.label, fontSize);
    const int center_x = view.x + view.w / 2;
    const int center_y = view.y + view.h / 2;
    DrawText(view.label, center_x - textWidth / 2, center_y - fontSize / 2,
             view.h / 2, view.textColor);
  }
}

} // namespace ViewFuncs
