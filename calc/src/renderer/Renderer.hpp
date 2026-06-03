#pragma once

namespace Renderer {

// Setup Stuff
bool Init(int width, int height, const char *title);
void Destroy();

// Drawing Functions
void BeginDrawing();
void EndDrawing();

void FillRect(int x, int y, int w, int h);
void StrokeRect(int x, int y, int w, int h);

}; // namespace Renderer
