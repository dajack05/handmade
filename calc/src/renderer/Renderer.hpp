#pragma once

#include "lib/glm/fwd.hpp"

namespace Renderer {

// Setup Stuff
bool Init(int width, int height, const char *title);
void Destroy();

// Drawing Functions
void BeginDrawing();
void EndDrawing();

void SetStyle(glm::vec4 bgColor, glm::vec4 borderColor, int borderThickness,
              glm::vec4 radius);
void FillRect(int x, int y, int w, int h);

// Util Functions
bool WindowCloseRequested();
double DeltaTime();
glm::ivec2 WindowSize();

}; // namespace Renderer
