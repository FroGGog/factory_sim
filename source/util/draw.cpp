#include "util/draw.hpp"
#include <raymath.h>

// Helper functions

Vector2 getScreenSize() {
   return {(float)GetScreenWidth(), (float)GetScreenHeight()};
}

Vector2 getScreenCenter() {
   return getOrigin(getScreenSize());
}

Vector2 getCenterOffset(const Vector2 &offset) {
   return Vector2Add(getScreenCenter(), offset);
}

Vector2 getTextOrigin(const Font &font, const char *text, float fontSize) {
   return getOrigin(MeasureTextEx(font, text, fontSize, 1.0f));
}

Vector2 getOrigin(const Vector2 &size) {
   return Vector2Scale(size, 0.5f);
}

Rectangle getBox(const Texture &texture) {
   return {0.0f, 0.0f, (float)texture.width, (float)texture.height};
}

Rectangle getRectangle(const Vector2 &position, const Vector2 &size) {
   return {position.x, position.y, size.x, size.y};
}

// Render functions

void drawTextCentered(const Font &font, const Vector2 &position, const char *text, float fontSize) {
   DrawTextPro(font, text, position, getTextOrigin(font, text, fontSize), 0.0f, fontSize, 1.0f, WHITE);
}

void drawTextureCentered(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), getOrigin(size), rotation, WHITE);
}

void drawTexture(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), {0.0f, 0.0f}, rotation, WHITE);
}
