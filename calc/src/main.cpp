#include "lib/stb/stb_sprintf.h"
#include "src/Colors.hpp"
#include "src/Layout.hpp"
#include "src/Stats.hpp"
#include "src/View.hpp"
#include "src/calculator/Calc.hpp"
#include "src/calculator/DigiOp.hpp"
#include "src/tests/Tests.hpp"
#include "src/util/String.hpp"

#include <cmath>
#include <raylib.h>

void drawNumbers();
void drawOperators(bool vertical);
void handleKeyboardInput();

const char *KEYS[12] = {
    "7", "8", "9", //
    "4", "5", "6", //
    "1", "2", "3", //
    ".", "0", "=", //
};

const char *OPS[8] = {"(", ")", "+", "-", "×", "÷", "C", "<-"};

DigiOpList eq;

double result = 0.0;
char resultStr[VIEW_MAX_LABEL_LEN] = {0};

void updateResult() {
  result = Calc::CalculateResult(eq);

  char tempResultStr[VIEW_MAX_LABEL_LEN] = {0};
  eq.toString(tempResultStr, VIEW_MAX_LABEL_LEN);
  stbsp_snprintf(resultStr, VIEW_MAX_LABEL_LEN, "%s = %f", tempResultStr,
                 result);
}

void handleClear() {
  eq.clear();
  eq.push({0.0});
  updateResult();
}

void handleEquals() {
  // TODO: Do we still need this?
  updateResult();
}

void handleNumber(unsigned int key) {
  DigiOp &digit = eq.last();
  if (digit.isOp()) {
    eq.push({(double)key});
  } else {
    digit.value = digit.value * 10.0 + (double)key;
  }
  // TODO: Handle decimals...
  // if (resultWritePos > 0) {
  //   *writeTo += (double)key / pow(10, resultWritePos);
  //   resultWritePos++;
  // }
  updateResult();
}

void loadOp(Op newOp) {
  eq.push({0.0, newOp});
  updateResult();
}

void setDecimal() {
  // TODO
  //  if (resultWritePos == 0) {
  //    resultWritePos = 1;
  //  }
}

void backspace() {
  DigiOp &digit = eq.last();
  if (digit.value >= 10) {
    digit.value = floor(digit.value / 10.0f);
  } else {
    eq.erase(eq.size() - 1);
  }
  updateResult();

  // TODO: Handle decimals
  // if (resultWritePos > 1) {
  //   // Delete from past remainder
  //   resultWritePos--;
  //   const int offset = pow(10, resultWritePos - 1);
  //   double offset_value = *writeTo * offset;
  //   offset_value = floor(offset_value);
  //   *writeTo = offset_value / offset;
  //   if (resultWritePos == 1) {
  //     resultWritePos = 0;
  //   }
  // }
}

void OnOpsClicked(const View &view) {
  if (StrEqual(view.tag, "+")) {
    loadOp(Op::Add);
  } else if (StrEqual(view.tag, "-")) {
    loadOp(Op::Subtract);
  } else if (StrEqual(view.tag, "×")) {
    loadOp(Op::Multiply);
  } else if (StrEqual(view.tag, "÷")) {
    loadOp(Op::Divide);
  } else if (StrEqual(view.tag, "(")) {
    loadOp(Op::ParenOpen);
  } else if (StrEqual(view.tag, ")")) {
    loadOp(Op::ParenClose);
  } else if (StrEqual(view.tag, "C")) {
    handleClear();
  } else if (StrEqual(view.tag, "<-")) {
    backspace();
  }
}

void OnKeypadClicked(const View &view) {
  // TODO: Handle decimals
  // if (StrEqual(view.tag, ".") && resultWritePos == 0) {
  //   resultWritePos = 1;
  //   return;
  // }
  if (StrEqual(view.tag, "=")) {
    handleEquals();
    return;
  }
  int key = StrToInt(view.tag);
  handleNumber(key);
}

int main(int argc, char **argv) {

  if (!RunTests()) {
    return 1;
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 500, "Calc");
  SetWindowMinSize(300, 300);
  SetTargetFPS(60);

  handleClear();
  unsigned long frameCount = 0;

  while (!WindowShouldClose()) {
    const bool layout_vertical = GetScreenWidth() < GetScreenHeight();
    frameCount++;
    handleKeyboardInput();

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
      Layout::BeginHBox({.bgColor = NONE}, SizeGrow, SizeFit, 10, 0);
      {
        // Result bar
        Layout::Text(
            {
                .roundness = 0.25f,
                .padding = 5,
                .bgColor = Colors.light,
                .textColor = Colors.dark,
            },
            SizeGrow, 50, resultStr);
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
    for (auto i = 0; i < 8; i++) {
      Layout::Button(
          {
              .roundness = 0.25f,
          },
          SizeGrow, SizeGrow, OPS[i], OnOpsClicked, false, OPS[i], NONE,
          Colors.accent);
    }
  }
  Layout::EndView();
}

void handleKeyboardInput() {
  if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)) {
    for (auto kp_key = 0; kp_key <= 9; kp_key++) {
      if (IsKeyPressed(KEY_KP_0 + kp_key) || IsKeyPressed(KEY_ZERO + kp_key)) {
        handleNumber(kp_key);
      }
    }
  }

  const bool equal = IsKeyPressed(KEY_EQUAL) && !IsKeyDown(KEY_LEFT_SHIFT) &&
                     !IsKeyDown(KEY_RIGHT_SHIFT);
  if (equal || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) ||
      IsKeyPressed(KEY_KP_EQUAL)) {
    handleEquals();
  }

  const bool plus = IsKeyPressed(KEY_EQUAL) &&
                    (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
  if (plus || IsKeyPressed(KEY_KP_ADD)) {
    loadOp(Op::Add);
  }

  if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
    loadOp(Op::Subtract);
  }

  const bool mult = IsKeyPressed(KEY_EIGHT) &&
                    (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
  if (mult || IsKeyPressed(KEY_KP_MULTIPLY)) {
    loadOp(Op::Multiply);
  }

  const bool divide = IsKeyPressed(KEY_SLASH) && !IsKeyDown(KEY_LEFT_SHIFT) &&
                      !IsKeyDown(KEY_RIGHT_SHIFT);
  if (divide || IsKeyPressed(KEY_KP_DIVIDE)) {
    loadOp(Op::Divide);
  }

  const bool period = IsKeyPressed(KEY_PERIOD) && !IsKeyDown(KEY_LEFT_SHIFT) &&
                      !IsKeyDown(KEY_RIGHT_SHIFT);
  if (period || IsKeyPressed(KEY_KP_DECIMAL)) {
    setDecimal();
  }

  if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_DELETE)) {
    backspace();
  }
}
