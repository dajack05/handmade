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
          // .w = GetScreenWidth(),
          .h = GetScreenHeight(),
          .roundness = 0.3f,
          .padding = 10,
          .gap = 10,
          .bgColor = ORANGE,
          .layoutDirection =
              vert ? LayoutDirection::Vertical : LayoutDirection::Horizontal,
      });
      {
        Layout::BeginView({
            .type = ViewType::Button,
            .x = 0,
            .y = 0,
            .w = 100,
            .h = 100,
            .roundness = 0.1f,
            .bgColor = RED,
            .onClickFunc = OnBtnClick,
        });
        Layout::EndView();
        if (show_red) {
          Layout::BeginView({
              .x = 0,
              .y = 0,
              .w = 100,
              .h = SizeGrow,
              .roundness = 0.1f,
              .bgColor = GREEN,
          });
          Layout::EndView();
        }
        Layout::BeginView({
            .x = 0,
            .y = 0,
            .w = 100,
            .h = 100,
            // .h = 100,
            .roundness = 0.1f,
            .bgColor = BLUE,
        });
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
