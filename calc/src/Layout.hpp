#pragma once

#include "src/View.hpp"

namespace Layout {

void BeginFrame();
void EndFrame();

void BeginView(View view);
void EndView();

void BeginPane(View view, int width, int height, const char *tag = "");
void Button(View view, int width, int height, const char *label,
            void (*onClickFunc)(const View &view), bool accent = false,
            const char *tag = "");
void Text(View view, int width, int height, const char *text,
          const char *tag = "");
void BeginHBox(View view, int width, int height, int padding = 10, int gap = 10,
               const char *tag = "");
void BeginVBox(View view, int width, int height, int padding = 10, int gap = 10,
               const char *tag = "");

}; // namespace Layout
