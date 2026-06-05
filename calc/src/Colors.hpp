#pragma once

#include "lib/glm/vec4.hpp"
#include <raylib.h>

#define RayToCol(ray)                                                          \
  {ray.r / 255.0f, ray.g / 255.0f, ray.b / 255.0f, ray.a / 255.0f}

const struct {
  const glm::vec4 dark = RayToCol(GetColor(0x222222FF));
  const glm::vec4 light = RayToCol(GetColor(0xFEFEFEFF));
  const glm::vec4 primary = RayToCol(GetColor(0x19647EFF));
  const glm::vec4 primary_lt = RayToCol(GetColor(0x28AFB0FF));
  const glm::vec4 accent = RayToCol(GetColor(0xFF6B6BFF));
  const glm::vec4 accent_lt = RayToCol(GetColor(0x92140CFF));
} Colors;
