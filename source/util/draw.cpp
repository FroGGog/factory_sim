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

// Helper functions

Vector2 getScreenSize() {
   return {(float)GetScreenWidth(), (float)GetScreenHeight()};
}

Vector2 getScreenCenter() {
   return getOrigin(getScreenSize());
}

Vector2 getCenterOffset(Vector2 offset) {
   return Vector2Add(getScreenCenter(), offset);
}

Vector2 getResponsivePos(float screenWidthRatio, float screenHeightRatio) {
   return {GetScreenWidth() * screenWidthRatio, GetScreenHeight() * screenHeightRatio};
}

Vector2 translateFromResponsivePos(Vector2 position) {
   return {position.x / GetScreenWidth(), position.y / GetScreenHeight()};
}

Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing);
}

Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing) {
   return getOrigin(MeasureTextEx(font, text, fontSize, spacing));
}

Vector2 getOrigin(Vector2 size) {
   return Vector2Scale(size, 0.5f);
}

Rectangle getBox(Texture texture) {
   return {0.0f, 0.0f, (float)texture.width, (float)texture.height};
}

Rectangle getRectangle(Vector2 position, Vector2 size) {
   return {position.x, position.y, size.x, size.y};
}

// Render functions

void drawText(Font font, Vector2 position, const char *text, float fontSize, Color color) {
   DrawTextPro(font, text, position, {0, 0}, 0.0f, fontSize, 1.0f, color);
}

void drawTextCentered(Font font, Vector2 position, const char *text, float fontSize, Color color) {
   DrawTextPro(font, text, position, getTextOrigin(font, text, fontSize, 1.0f), 0.0f, fontSize, 1.0f, color);
}

void drawTextResponsive(Font font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color) {
   float fontSizeScaled = getFontSize(fontSize);
   float fontSpacingScaled = getFontSize(1.0f);
   DrawTextPro(font, text, getResponsivePos(screenWidthRatio, screenHeightRatio), {0, 0}, 0.0f, fontSizeScaled, fontSpacingScaled, color);
}

void drawTextResponsiveCentered(Font font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color) {
   float fontSizeScaled = getFontSize(fontSize);
   float fontSpacingScaled = getFontSize(1.0f);
   DrawTextPro(font, text, getResponsivePos(screenWidthRatio, screenHeightRatio), getTextOrigin(font, text, fontSizeScaled, fontSpacingScaled), 0.0f, fontSizeScaled, fontSpacingScaled, color);
}

void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), {0.0f, 0.0f}, rotation, color);
}

void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(position, size), getOrigin(size), rotation, color);
}

void drawTextureResponsive(Texture texture, float screenWidthRatio, float screenHeightRatio, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getBox(texture), getRectangle(getResponsivePos(screenWidthRatio, screenHeightRatio), Vector2Scale(size, getCubicRatio())), {0.0f, 0.0f}, rotation, color);
}

void drawTextureResponsiveCentered(Texture texture, float screenWidthRatio, float screenHeightRatio, Vector2 size, Color color, float rotation) {
   Vector2 sizeScaled = Vector2Scale(size, getCubicRatio());
   DrawTexturePro(texture, getBox(texture), getRectangle(getResponsivePos(screenWidthRatio, screenHeightRatio), sizeScaled), getOrigin(sizeScaled), rotation, color);
}

// Buttons

void Button::initTextButton(Font font, Vector2 position, const std::string &text, float fontSize) {
   this->font = font;
   this->position = position;
   this->size = getTextSize(font, text.c_str(), fontSize, 1.0f);
   this->text = text;
   this->fontSize = fontSize;
}

void Button::initButton(Font font, Texture *texture, Vector2 position, Vector2 size, const std::string &text, float fontSize) {
   this->font = font;
   this->texture = texture;
   this->position = position;
   this->size = size;
   this->text = text;
   this->fontSize = fontSize;
}

void Button::update(float dt) {
   Vector2 mouse = GetMousePosition();
   Vector2 sizeScaled = Vector2Scale(size, getCubicRatio());

   hovering = CheckCollisionPointRec(mouse, getRectangle(getResponsivePos(position.x, position.y), sizeScaled));
   down = hovering && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
   clicked = hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

   if (down) {
      scale = fmaxf(scale - dt, buttonScaleMin);
   }
   else if (hovering) {
      scale = fminf(scale + dt, buttonScaleMax);
   }
   else if (scale < 1.0f) {
      scale = fminf(scale + dt, 1.0f);
   }
   else if (scale > 1.0f) {
      scale = fmaxf(scale - dt, 1.0f);
   }
}

void Button::draw() {
   Vector2 realPos = Vector2Add(position, translateFromResponsivePos(Vector2Scale(size, getCubicRatio() * 0.5f)));
   
   if (texture) {
      drawTextureResponsiveCentered(*texture, realPos.x, realPos.y, Vector2Scale(size, scale), WHITE);
   }
   drawTextResponsiveCentered(font, realPos.x, realPos.y, text.c_str(), fontSize * scale, textColor);
}
