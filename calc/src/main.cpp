#include "src/Calc.hpp"
#include "src/Layout.hpp"
#include "src/Stats.hpp"
#include "src/View.hpp"
#include "src/tests/Tests.hpp"
#include "src/util/String.hpp"

#include <cmath>
#include <cstring>
#include <raylib.h>

void drawNumbers();
void drawOperators(bool vertical);
const char *calcResultStr();

const char *KEYS[12] = {
    "7", "8", "9", //
    "4", "5", "6", //
    "1", "2", "3", //
    ".", "0", "=", //
};

const char *OPS[5] = {
    "+", "-", "×", "÷", "C",
};

double result = 0.0;
double first = 0.0;
double second = 0.0;
double *writeTo = &first;
bool resultValid = false;
Calc::Op op = Calc::Op::None;

int resultWritePos = 0;
char resultStr[VIEW_MAX_LABEL_LEN] = {0};

void OnOpsClicked(const View &view) {
  writeTo = &second;
  result = 0.0;
  resultWritePos = 0;
  if (StrEqual(view.tag, "+")) {
    op = Calc::Op::Add;
  } else if (StrEqual(view.tag, "-")) {
    op = Calc::Op::Sub;
  } else if (StrEqual(view.tag, "×")) {
    op = Calc::Op::Mult;
  } else if (StrEqual(view.tag, "÷")) {
    op = Calc::Op::Div;
  } else if (StrEqual(view.tag, "C")) {
    result = 0.0;
    first = 0.0;
    second = 0.0;
    writeTo = &first;
    resultValid = false;
    op = Calc::Op::None;
  }
}

void OnKeypadClicked(const View &view) {
  if (StrEqual(view.tag, ".") && resultWritePos == 0) {
    resultWritePos = 1;
    return;
  }
  if (StrEqual(view.tag, "=")) {
    result = Calc::PerformInFix(first, second, op);
    resultWritePos = 0.0;
    first = result;
    writeTo = &first;
    resultValid = true;
    return;
  }
  int key = StrToInt(view.tag);
  if (resultWritePos > 0) {
    *writeTo += (double)key / pow(10, resultWritePos);
    resultWritePos++;
  } else {
    *writeTo = *writeTo * 10 + key;
  }

  result = Calc::PerformInFix(first, second, op);
}

int main(int argc, char **argv) {

  if (!RunTests()) {
    return 1;
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 500, "Calc");
  SetWindowMinSize(300, 300);
  SetTargetFPS(60);

  unsigned long frameCount = 0;

  while (!WindowShouldClose()) {
    const bool layout_vertical = GetScreenWidth() < GetScreenHeight();
    frameCount++;

    BeginDrawing();
    ClearBackground(BLACK);

    Layout::BeginFrame();
    Layout::BeginVBox(
        {
            .bgColor = Colors.primary,
            .layoutDirection = LayoutDirection::Vertical,
        },
        GetScreenWidth(), GetScreenHeight(), 0);
    {
      Layout::BeginVBox({.bgColor = NONE}, SizeGrow, SizeFit, 10, 0);
      {
        // Result bar
        Layout::Text(
            {
                .roundness = 0.25f,
                .padding = 5,
                .bgColor = Colors.light,
                .textColor = Colors.dark,
            },
            SizeGrow, 50, calcResultStr());
      }
      Layout::EndView();

      if (layout_vertical) {
        Layout::BeginVBox({}, SizeGrow, SizeGrow, 0);
      } else {
        Layout::BeginHBox({}, SizeGrow, SizeGrow, 0);
      }
      {
        // Main container
        if (layout_vertical) {
          drawOperators(false);
          drawNumbers();
        } else {
          drawNumbers();
          drawOperators(true);
        }
      }
      Layout::EndView();
    }
    Layout::EndView();

    Layout::EndFrame();

    EndDrawing();

    if (frameCount % 60 == 0) {
      Stats::Print();
    }
  }

  CloseWindow();

  return 0;
}

void drawNumbers() {
  Layout::BeginVBox({}, SizeGrow, SizeGrow, 5, 0);
  {
    // Numbers
    for (auto y = 0; y < 4; y++) {
      Layout::BeginHBox({}, SizeGrow, SizeGrow, 5);
      for (auto x = 0; x < 3; x++) {
        const unsigned int idx = x + y * 3;
        const char *lbl = KEYS[idx];
        Layout::Button({.roundness = 0.25f}, SizeGrow, SizeGrow, lbl,
                       OnKeypadClicked, idx == 11, lbl);
      }
      Layout::EndView();
    }
  }
  Layout::EndView();
}

void drawOperators(bool vertical) {
  if (vertical) {
    Layout::BeginVBox({.bgColor = Colors.primary_lt}, 80, SizeGrow);
  } else {
    Layout::BeginHBox({.bgColor = Colors.primary_lt}, SizeGrow, 80);
  }
  {
    // functions
    for (auto i = 0; i < 5; i++) {
      Layout::Button(
          {
              .roundness = 0.25f,
              .borderThickness = i + 1 == (int)op ? 4 : 0,
          },
          SizeGrow, SizeGrow, OPS[i], OnOpsClicked, false, OPS[i]);
    }
  }
  Layout::EndView();
}

const char *calcResultStr() {
  if (op == Calc::Op::None) {
    return StrFromDouble(*writeTo);
  } else if (resultValid) {
    return StrFromDouble(result);
  }
  char c = '?';
  return TextFormat("%g %c %g = %g", first, c, second, result);
}
