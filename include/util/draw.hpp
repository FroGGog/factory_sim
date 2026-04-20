#ifndef UTIL_DRAW_HPP
#define UTIL_DRAW_HPP

#include <raylib.h>

// Responsive design functions

float getWidthRatio();
float getHeightRatio();
float getCubicRatio();
float getFontSize(float size);

void drawTextResponsiveCentered(const Font &font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color);
void drawTextResponsive(const Font &font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color);

// Helper functions

Vector2 getScreenSize();
Vector2 getScreenCenter();
Vector2 getCenterOffset(const Vector2 &offset);

Vector2 getResponsivePos(float screenWidthRatio, float screenHeightRatio);
Rectangle getResponsiveTextRectangle(float screenWidthRatio, float screenHeightRatio, const Font &font, const char *text, float fontSize);

Vector2 getTextOrigin(const Font &font, const char *text, float fontSize, float spacing);
Vector2 getOrigin(const Vector2 &size);

Rectangle getBox(const Texture &texture);
Rectangle getRectangle(const Vector2 &position, const Vector2 &size);

// Render functions

void drawTextCentered(const Font &font, const Vector2 &position, const char *text, float fontSize);

void drawTextureCentered(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation = 0.0f);
void drawTexture(const Texture &texture, const Vector2 &position, const Vector2 &size, float rotation = 0.0f);

#endif
