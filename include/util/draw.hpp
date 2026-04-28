#ifndef UTIL_DRAW_HPP
#define UTIL_DRAW_HPP

#include <raylib.h>
#include <string>

// Responsive design functions

float getWidthRatio();
float getHeightRatio();
float getCubicRatio();
float getFontSize(float size);

// Helper functions

Vector2 getScreenSize();
Vector2 getScreenCenter();
Vector2 getCenterOffset(Vector2 offset);

Vector2 getResponsivePos(float screenWidthRatio, float screenHeightRatio);
Vector2 translateFromResponsivePos(Vector2 position);

Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing);
Vector2 getOrigin(Vector2 size);

Rectangle getBox(Texture texture);
Rectangle getRectangle(Vector2 position, Vector2 size);

// Render functions

void drawText(Font font, Vector2 position, const char *text, float fontSize, Color color);
void drawTextCentered(Font font, Vector2 position, const char *text, float fontSize, Color color);
void drawTextResponsive(Font font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color);
void drawTextResponsiveCentered(Font font, float screenWidthRatio, float screenHeightRatio, const char *text, float fontSize, Color color);

void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color, float rotation = 0.0f);
void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, float screenWidthRatio, float screenHeightRatio, Vector2 size, Color color, float rotation = 0.0f);
void drawTextureResponsiveCentered(Texture texture, float screenWidthRatio, float screenHeightRatio, Vector2 size, Color color, float rotation = 0.0f);

// Buttons

struct Button {
   void initTextButton(Font font, Vector2 position, const std::string &text, float fontSize);
   void initButton(Font font, Texture *texture, Vector2 position, Vector2 size, const std::string &text, float fontSize);

   void update(float dt);
   void draw();

   // Members

   Font font; // required
   Texture *texture = nullptr; // optional
   Vector2 position, size;
   Color textColor = WHITE;
   std::string text;

   bool hovering = false;
   bool down = false;
   bool clicked = false;
   float scale = 1.0f;
   float fontSize = 0.0f;

   float buttonScaleMin = 0.95f;
   float buttonScaleMax = 1.05f;
};

#endif
