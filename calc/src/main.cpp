#include "src/Layout.hpp"
#include "src/Stats.hpp"
#include "src/View.hpp"
#include "src/tests/Tests.hpp"
#include "src/util/String.hpp"
#include <cstdio>
#include <cstring>
#include <raylib.h>

const char *KEYS[12] = {
    "7", "8", "9", //
    "4", "5", "6", //
    "1", "2", "3", //
    " ", "0", " ", //
};

double result = 0.0;
char resultStr[VIEW_MAX_LABEL_LEN] = {0};

void OnKeypadClicked(const View &view) {
  int key = StrToInt(view.tag);
  printf("Key: %i\n", key);
}

int main(int argc, char **argv) {

  if (!RunTests()) {
    return 1;
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 600, "Calc");
  SetTargetFPS(60);

  unsigned long frameCount = 0;

  while (!WindowShouldClose()) {
    frameCount++;

    BeginDrawing();
    ClearBackground(BLACK);

    Layout::BeginFrame();
    Layout::BeginVBox({.layoutDirection = LayoutDirection::Vertical},
                      GetScreenWidth(), GetScreenHeight());
    {
      // Result bar
      Layout::Text(
          {
              .padding = 5,
              .bgColor = Colors.light,
              .textColor = Colors.dark,
          },
          SizeGrow, 50, TextFormat("%f", result));

      Layout::BeginHBox({}, SizeGrow, SizeGrow, 0);
      {
        // Main container
        Layout::BeginVBox({}, SizeGrow, SizeGrow, 0, 0);
        {
          // Numbers
          for (auto y = 0; y < 4; y++) {
            Layout::BeginHBox({}, SizeGrow, SizeGrow, 5);
            for (auto x = 0; x < 3; x++) {
              const unsigned int idx = x + y * 3;
              if (idx == 9 || idx == 11) {
                Layout::BeginView({.w = SizeGrow, .h = SizeGrow});
                Layout::EndView();
              } else {
                const char *lbl = KEYS[idx];
                Layout::Button({}, SizeGrow, SizeGrow, lbl, OnKeypadClicked,
                               false, lbl);
              }
            }
            Layout::EndView();
          }
        }
        Layout::EndView();
        Layout::BeginVBox({.bgColor = RED}, 80, SizeGrow);
        {
          // functions
        }
        Layout::EndView();
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
