#include "Layout.hpp"
#include "src/Stats.hpp"
#include "src/View.hpp"
#include "src/ViewFuncs.hpp"
#include "src/util/List.hpp"
#include "src/util/Math.hpp"
#include "src/util/String.hpp"
#include <cstdio>
#include <raylib.h>

#define CACHE_SIZE 1024

namespace Layout {

const unsigned int NO_PARENT = CACHE_SIZE + 1;
const unsigned int NO_CHILD = CACHE_SIZE + 1;

struct CachedView {
  View view;
  int start_w = SizeFit;
  int start_h = SizeFit;
  int content_width = 0;
  int content_height = 0;

  int child_offset = 0;
  int child_idx = 0;

  unsigned int parent = NO_PARENT;
  List<unsigned int, 128> children = List<unsigned int, 128>(NO_CHILD);
};

struct AxisPackedDims {
  int &on_axis_pos;
  int &off_axis_pos;
  int &on_axis_size;
  int &off_axis_size;
};

double layout_start = 0.0;

List<CachedView, CACHE_SIZE> viewCache;
List<unsigned int, CACHE_SIZE> viewStack;

void calcSize(CachedView &view);
bool calcGrow(CachedView &view);
void calcPosition(CachedView &view);
void checkInput(CachedView &view);

CachedView *getParent(CachedView &view) {
  if (view.parent == NO_PARENT) {
    return nullptr;
  }
  return &viewCache.get(view.parent);
}

AxisPackedDims getAxisDims(CachedView &view) {
  CachedView *parent = getParent(view);
  bool x = parent
               ? (parent->view.layoutDirection == LayoutDirection::Horizontal)
               : view.view.layoutDirection == LayoutDirection::Horizontal;
  return {
      x ? view.view.x : view.view.y,
      x ? view.view.y : view.view.x,
      x ? view.view.w : view.view.h,
      x ? view.view.h : view.view.w,
  };
}

void BeginView(View view) {
  if (!view.renderFunc) {
    switch (view.type) {
    case ViewType::View:
      view.renderFunc = ViewFuncs::RenderView;
      break;
    case ViewType::Button:
      view.renderFunc = ViewFuncs::RenderButton;
      break;
    }
  }
  unsigned int parent_id = NO_PARENT;
  if (viewStack.count() > 0) {
    parent_id = viewStack.get(viewStack.count() - 1);
  }
  const unsigned int idx = viewCache.push({
      view,
      view.w,
      view.h,
      0,
      0,
      0,
      0,
      parent_id,
  });
  viewStack.push(idx);
}

void EndView() {
  if (viewStack.count() == 0) {
    printf("LAYOUT ERROR: viewStackIdx == 0. `EndView()` called too many "
           "times.\n");
    return;
  }

  CachedView &view = viewCache.get(viewStack.last());

  calcSize(view);

  CachedView *parent = getParent(view);
  if (parent) {
    view.child_idx = parent->children.count();
    parent->children.push(viewStack.last());
  }

  viewStack.pop();
}

void BeginFrame() {
  viewCache.clear();
  viewStack.clear();
  layout_start = GetTime();
}

void EndFrame() {
  if (viewStack.count() != 0) {
    printf("LAYOUT ERROR: stack index != 0. You're probably missing a call to "
           "`EndView`.\n");
    return;
  }

  for (auto i = 0; i < viewCache.count(); i++) {
    CachedView &view = viewCache.get(i);

    calcPosition(view);
    if (calcGrow(view)) {
      i = 0;
    }
  }

  for (auto i = 0; i < viewCache.count(); i++) {
    CachedView &view = viewCache.get(i);

    checkInput(view);

    if (view.view.renderFunc) {
      view.view.renderFunc(view.view);
      continue;
    }
  }

  double time = GetTime() - layout_start;
  double ms = (unsigned int)(time * 1000.0f);
  Stats::Update("Layout Time", ms);
}

void calcSize(CachedView &view) {
  AxisPackedDims axis = getAxisDims(view);
  CachedView *parent = getParent(view);
  if (parent) {
    switch (parent->view.layoutDirection) {
    case LayoutDirection::Horizontal:
      parent->content_width += view.view.w;
      parent->content_height = max(parent->content_height, view.view.h);
      break;
    case LayoutDirection::Vertical:
      parent->content_height += view.view.h;
      parent->content_width = max(parent->content_width, view.view.w);
      break;
    }
  }

  if (view.children.count() > 1) {
    switch (view.view.layoutDirection) {
    case LayoutDirection::Horizontal:
      view.content_width += view.view.gap * (view.children.count() - 1);
      break;
    case LayoutDirection::Vertical:
      view.content_height += view.view.gap * (view.children.count() - 1);
      break;
    }
  }

  view.content_width += view.view.padding * 2;
  view.content_height += view.view.padding * 2;

  if (view.view.w != SizeGrow) {
    view.view.w = max(view.view.w, view.content_width);
  }
  if (view.view.h != SizeGrow) {
    view.view.h = max(view.view.h, view.content_height);
  }
}

bool calcGrow(CachedView &view) {
  CachedView *parent = getParent(view);
  bool didChange = false;
  if (parent) {
    AxisPackedDims axis = getAxisDims(view);
    AxisPackedDims parentAxis = getAxisDims(*parent);
    if (axis.on_axis_size == SizeGrow) {
      const int total_size = parentAxis.on_axis_size;
      const int padded_size = total_size - parent->view.padding * 2;
      const int gapped_size =
          padded_size - (parent->children.count() - 1) * parent->view.gap;
      int sibling_size = 0;
      int siblings_grow = 0;
      for (auto sibi = 0; sibi < parent->children.count(); sibi++) {
        if (sibi == view.child_idx)
          continue;
        AxisPackedDims sibAxis =
            getAxisDims(viewCache.get(parent->children.get(sibi)));
        sibling_size += sibAxis.on_axis_size;
        if (sibAxis.on_axis_size == SizeGrow) {
          siblings_grow++;
        }
      }
      const int after_sibling_size = gapped_size - sibling_size;
      const int final_size = after_sibling_size / (siblings_grow + 1);
      if (axis.on_axis_size != final_size) {
        axis.on_axis_size = final_size;
        parent->child_offset = 0;
        didChange = true;
      }
    }
    if (axis.off_axis_size == SizeGrow) {
      const int total_size = parentAxis.off_axis_size;
      const int final_size = total_size - parent->view.padding * 2;
      if (axis.off_axis_size != final_size) {
        axis.off_axis_size = final_size;
        // didChange = true;
      }
    }
  }
  return didChange;
}

void calcPosition(CachedView &view) {

  CachedView *parent = getParent(view);
  if (parent) {
    const int gap = parent->view.gap * view.child_idx;
    AxisPackedDims axis = getAxisDims(view);
    AxisPackedDims parentAxis = getAxisDims(*parent);
    view.view.x = parent->view.x;
    view.view.y = parent->view.y;
    axis.on_axis_pos += parent->child_offset + parent->view.padding + gap;
    axis.off_axis_pos += parent->view.padding;
    parent->child_offset += axis.on_axis_size;
  }
}

void checkInput(CachedView &view) {
  const Rectangle rect{
      (float)view.view.x,
      (float)view.view.y,
      (float)view.view.w,
      (float)view.view.h,
  };

  if (CheckCollisionPointRec(GetMousePosition(), rect)) {
    view.view.state = ViewState::Hover;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      view.view.state = ViewState::Active;
    }
  }
}
}; // namespace Layout
