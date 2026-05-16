#pragma once

#include <raylib.h>

enum class ViewType {
  View,
  Button,
};

enum class LayoutDirection {
  Horizontal,
  Vertical,
};

enum class ViewState {
  None,
  Hover,
  Active,
  Focus,
};

const int SizeFit = 0;
const int SizeGrow = -1;

struct View {
  ViewType type = ViewType::View;
  int x = 0;
  int y = 0;
  int w = SizeFit;
  int h = SizeFit;

  float roundness = 0.0f;

  int padding = 0;
  int gap = 0;

  Color bgColor = BLACK;
  Color borderColor = BLACK;
  int borderThickness = 0;

  ViewState state = ViewState::None;
  LayoutDirection layoutDirection = LayoutDirection::Horizontal;

  void (*renderFunc)(const View &) = nullptr;
  void (*onClickFunc)(void) = nullptr;
};
