#pragma once

#include "lib/glm/vec4.hpp"

namespace Renderer {

// Setup Stuff
bool Init(int width, int height, const char *title);
void Destroy();

// Drawing Functions
void BeginDrawing();
void EndDrawing();

void FillRect(int x, int y, int w, int h, glm::vec4 color);

// Util Functions
bool WindowCloseRequested();

}; // namespace Renderer
