#include <stdlib.h>
#include "raylib.h"
#include <cstdio>

void writeTextInScreenAtCenter(const char *text, float fontsize, float fontSpacing, int xOffset, int yOffset)
{
  Vector2 measureText = MeasureTextEx(GetFontDefault(), text, fontsize, fontSpacing);
  DrawTextEx(GetFontDefault(),
              text,
              Vector2{(float) GetScreenWidth() / 2 - (measureText.x / 2) + xOffset, (float) GetScreenHeight() / 2 - (measureText.y) + yOffset},
              fontsize, fontSpacing,
              LIGHTGRAY);
}