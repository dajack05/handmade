#include "src/ViewFuncs.hpp"

#include "src/View.hpp"
#include "src/renderer/Renderer.hpp"
#include "src/util/String.hpp"
#include <cstdio>

namespace ViewFuncs {
void RenderView(const View &view) {
  Renderer::SetStyle(view.bgColor, view.borderColor, view.borderThickness,
                     glm::vec4(5));
  Renderer::FillRect(view.x, view.y, view.w, view.h);
  //   const Rectangle rect = {
  //       (float)view.x,
  //       (float)view.y,
  //       (float)view.w,
  //       (float)view.h,
  //   };
  //   if (view.bgColor.a != 0) {
  //     DrawRectangleRounded(rect, view.roundness, 8, view.bgColor);
  //   }
  //   if (view.borderThickness > 0) {
  //     DrawRectangleRoundedLinesEx(rect, view.roundness, 8,
  //     view.borderThickness,
  //                                 view.borderColor);
  //   }
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
  // if (StrLen(view.label) > 0) {
  //   const int fontSize = view.h / 2;
  //   const int textWidth = MeasureText(view.label, fontSize);
  //   const int center_x = view.x + view.w / 2;
  //   const int center_y = view.y + view.h / 2;
  //   DrawText(view.label, center_x - textWidth / 2, center_y - fontSize / 2,
  //            view.h / 2, view.textColor);
  // }
}

void RenderText(const View &view) {
  RenderView(view);
  // View nView = view;
  // if (StrLen(nView.label) > 0) {
  //   const int fontSize = nView.h / 2;
  //   const int elipsisWidth = MeasureText("...", fontSize);
  //   int textWidth = MeasureText(nView.label, fontSize);
  //   bool didResize = false;
  //   int count = 0;
  //   while (textWidth + elipsisWidth > nView.w - nView.padding * 2) {
  //     didResize = true;
  //     StrCopy(StrTrim(nView.label, 1), nView.label, VIEW_MAX_LABEL_LEN);
  //     textWidth = MeasureText(nView.label, fontSize);
  //     count++;
  //     if (count > 1000) {
  //       printf("RenderText() looped more than 1000 times to try and trim "
  //              "text... Probably an issue...\n");
  //       break;
  //     }
  //   }
  //   if (didResize) {
  //     StrCopy(StrAppend(nView.label, "..."), nView.label,
  //     VIEW_MAX_LABEL_LEN);
  //   }
  //   const int center_x = nView.x + nView.padding;
  //   const int center_y = nView.y + nView.h / 2;
  //   DrawText(nView.label, center_x, center_y - fontSize / 2, nView.h / 2,
  //            nView.textColor);
  // }
}

} // namespace ViewFuncs
