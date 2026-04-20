#include "game/menustate.hpp"
#include "game/gamestate.hpp"
#include "mngr/asset.hpp"
#include "util/draw.hpp"
#include "util/random.hpp"
#include <cmath>

// Constants

constexpr Vector2 titlePosRatio = {0.05f, 0.05f};
constexpr Vector2 playButtonPosRatio = {0.05f, 0.2f};
constexpr Vector2 quitButtonPosRatio = {0.05f, 0.3f};
constexpr float fontDefault = 50;
constexpr float fontTitle = 120;

// Constructor

MenuState::MenuState() {
   camera.position = {-0.5f, -8.0f, -13.0f};
   camera.target = {10, 10, 10};
   camera.up = {0, 1, 0};
   camera.fovy = 70.0f;
   camera.projection = CAMERA_PERSPECTIVE;

   for (int i = 0; i < 400; i++) {
      stars.push_back({
         {randomFloat(-200.0f, 200.0f), randomFloat(-200.0f, 200.0f), randomFloat(-200.0f, 200.0f)},
         randomColor(50, 255),
         randomFloat(0.1f, 0.5f),
         randomFloat(0.0f, 1.0f)
      });
   }
}

// Update

void MenuState::update() {
    float t = GetTime() * 0.1f;
    camera.position = {-0.5f + sinf(t) * 3.0f, -8.0f + cosf(t * 0.7f) * 1.5f, -13.0f};

   // temporary for now
   if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      return;
   }
   
   Font &font = getFont("sekuya");
   Rectangle playRect = getResponsiveTextRectangle(playButtonPosRatio.x, playButtonPosRatio.y, font, "play", fontDefault);
   Rectangle quitRect = getResponsiveTextRectangle(quitButtonPosRatio.x, quitButtonPosRatio.y, font, "quit", fontDefault);
   Vector2 mouse = GetMousePosition();

   if (CheckCollisionPointRec(mouse, playRect)) {
      playingALevel = true;
      quitState = true;
   }

   if (CheckCollisionPointRec(mouse, quitRect)) {
      quitState = true;
   }
}

void MenuState::fixedUpdate() {}

// Render

void MenuState::render() {
   BeginMode3D(camera);
      float sine = sin(GetTime() * 0.5f);   
      for (const Star &s: stars) {
         float alpha = 0.5f + fminf(1.0f, sine + s.twinkleOffset) * 0.5f;
         DrawSphereEx(s.pos, s.radius, 3, 3, Fade(s.color, alpha));
      }

      DrawSphere({0, 0, 0}, 5, YELLOW);
      DrawSphere({0, 0, 0}, 5.5f + sine * 0.10f, Fade(YELLOW, 0.666f - sine * 0.20f));
      DrawSphere({0, 0, 0}, 6.5f + sine * 0.20f, Fade(YELLOW, 0.333f - sine * 0.10f));
      DrawSphere({0, 0, 0}, 7.5f + sine * 0.30f, Fade(YELLOW, 0.066f - sine * 0.02f));
   EndMode3D();
   Font &font = getFont("sekuya");
   drawTextResponsive(font, titlePosRatio.x, titlePosRatio.y, "factory sim", fontTitle, RED);
   drawTextResponsive(font, playButtonPosRatio.x, playButtonPosRatio.y, "play", fontDefault, RED);
   drawTextResponsive(font, quitButtonPosRatio.x, quitButtonPosRatio.y, "quit", fontDefault, RED);
}

// Change

State *MenuState::change() {
   if (playingALevel) {
      return new MainGameState(GridSettings{5000, 5000, 64});
   }
   return nullptr;
}
