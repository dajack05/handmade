#pragma once

#include "src/Colors.hpp"

#define VIEW_MAX_LABEL_LEN 128
#define VIEW_MAX_TAG_LEN 32

enum class ViewType {
  View,
  Button,
  Text,
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

const glm::vec4 NONE{0, 0, 0, 0};

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

  glm::vec4 bgColor = Colors.dark;
  glm::vec4 borderColor = Colors.light;
  glm::vec4 textColor = Colors.light;
  int borderThickness = 0;

  ViewState state = ViewState::None;
  LayoutDirection layoutDirection = LayoutDirection::Horizontal;

  char tag[VIEW_MAX_TAG_LEN] = {0};
  char label[VIEW_MAX_LABEL_LEN] = {0};

  void (*renderFunc)(const View &) = nullptr;
  void (*onClickFunc)(const View &) = nullptr;
};
