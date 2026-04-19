#include "game/menustate.hpp"
#include "game/gamestate.hpp"
#include "mngr/asset.hpp"
#include <cmath>

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
   DrawTextPro(font, "FACTORY SIM", {20.0f, 20.0f}, {0, 0}, 0, 120.0f, 1.0f, RED);
}

// Change

State *MenuState::change() {
   if (playingALevel) {
      return new MainGameState(GridSettings{5000, 5000, 64});
   }
   return nullptr;
}
