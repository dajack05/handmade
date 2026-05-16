#pragma once

#include "src/View.hpp"

namespace Layout {

void BeginFrame();
void EndFrame();

void BeginView(View view);
void EndView();

}; // namespace Layout
