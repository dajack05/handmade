#include "src/Layout.hpp"
#include "src/Stats.hpp"
#include "src/View.hpp"
#include <cstring>
#include <raylib.h>

bool show_red = true;

void OnBtnClick() { show_red = !show_red; }

int main(int argc, char **argv) {
  InitWindow(400, 600, "Calc");
  SetTargetFPS(60);

  unsigned long frameCount = 0;

  bool vert = true;

  while (!WindowShouldClose()) {
    frameCount++;

    if (IsKeyPressed(KEY_SPACE)) {
      vert = !vert;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    Layout::BeginFrame();
    {
      Layout::BeginView({
          .x = 0,
          .y = 0,
          .w = GetScreenWidth(),
          .h = GetScreenHeight(),
          .padding = 10,
          .gap = 10,
          .bgColor = NONE,
          .layoutDirection =
              vert ? LayoutDirection::Vertical : LayoutDirection::Horizontal,
      });
      {
        Layout::BeginView({
            .w = SizeGrow,
            .h = SizeGrow,
            .padding = 10,
            .gap = 10,
            .bgColor = WHITE,
            .layoutDirection = LayoutDirection::Vertical,
        });
        {
          Layout::BeginView({
              .w = 100,
              .h = 100,
              .bgColor = RED,
          });
          Layout::EndView();
          Layout::BeginView({
              .w = 100,
              .h = 100,
              .bgColor = BLUE,
              .layoutDirection = LayoutDirection::Horizontal,
          });
          {
            Layout::BeginView({
                .w = 20,
                .h = 20,
                .bgColor = GREEN,
                .borderColor = RED,
                .borderThickness = 2,
            });
            Layout::EndView();
            Layout::BeginView({
                .w = 20,
                .h = 20,
                .bgColor = GREEN,
                .borderColor = RED,
                .borderThickness = 2,
            });
            Layout::EndView();
          }
          Layout::EndView();
        }
        Layout::EndView();
      }
      Layout::EndView();
    }
    Layout::EndFrame();

    EndDrawing();

    if (frameCount % 60 == 0) {
      Stats::Print();
    }
  }

  CloseWindow();

  return 0;
}
