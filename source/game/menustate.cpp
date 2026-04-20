#include "game/menustate.hpp"
#include "game/gamestate.hpp"
#include "mngr/asset.hpp"
#include "util/draw.hpp"
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
}

// Update

void MenuState::update() {
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
   // UpdateCamera(&camera, CAMERA_FREE);
}

void MenuState::fixedUpdate() {}

// Render

void MenuState::render() {
   BeginMode3D(camera);
      float sine = sin(GetTime() * 0.5f);   
    
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
