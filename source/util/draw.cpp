#include "util/draw.hpp"
#include <raymath.h>

// Responsive design functions

float getWidthRatio() {
   return GetScreenWidth() / 1920.0f;
}

float getHeightRatio() {
   return GetScreenHeight() / 1080.0f;
}

float getCubicRatio() {
   return fminf(getWidthRatio(), getHeightRatio());
}

float getFontSize(float size) {
   return size * getCubicRatio();
}

void drawTextResponsiveCentered(const Font &font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color) {
   float fontSizeScaled = getFontSize(fontSize);
   float fontSpacingScaled = getFontSize(1.0f);
   DrawTextPro(font, text, getResponsivePos(screenWidthRatio, screenHeightRatio), getTextOrigin(font, text, fontSizeScaled, fontSpacingScaled), 0.0f, fontSizeScaled, fontSpacingScaled, color);
}

void drawTextResponsive(const Font &font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color) {
   float fontSizeScaled = getFontSize(fontSize);
   float fontSpacingScaled = getFontSize(1.0f);
   DrawTextPro(font, text, getResponsivePos(screenWidthRatio, screenHeightRatio), {0, 0}, 0.0f, fontSizeScaled, fontSpacingScaled, color);
}

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

Vector2 getResponsivePos(float screenWidthRatio, float screenHeightRatio) {
   return {GetScreenWidth() * screenWidthRatio, GetScreenHeight() * screenHeightRatio};
}

Rectangle getResponsiveTextRectangle(float screenWidthRatio, float screenHeightRatio, const Font &font, const char *text, float fontSize) {
   Vector2 position = getResponsivePos(screenWidthRatio, screenHeightRatio);
   Vector2 size = MeasureTextEx(font, text, getFontSize(fontSize), getFontSize(1.0f));
   return getRectangle(position, size);
}

Vector2 getTextOrigin(const Font &font, const char *text, float fontSize, float spacing) {
   return getOrigin(MeasureTextEx(font, text, fontSize, spacing));
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
   DrawTextPro(font, text, position, getTextOrigin(font, text, fontSize, 1.0f), 0.0f, fontSize, 1.0f, WHITE);
}

void drawTextureCentered(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), getOrigin(size), rotation, WHITE);
}

void drawTexture(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), {0.0f, 0.0f}, rotation, WHITE);
}
