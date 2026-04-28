#include "game/menustate.hpp"
#include "game/gamestate.hpp"
#include "mngr/asset.hpp"
#include "util/draw.hpp"
#include "util/random.hpp"
#include <cmath>

// Constants

constexpr Vector2 titlePosRatio = {0.05f, 0.05f};
constexpr float fontDefault = 50;
constexpr float fontTitle = 120;

// Constructor

MenuState::MenuState() {
   Font font = getFont("protest-strike");
   playButton.initTextButton(font, {0.05f, 0.2f}, "PLAY", fontDefault);
   quitButton.initTextButton(font, {0.05f, 0.3f}, "QUIT", fontDefault);
   playButton.textColor = quitButton.textColor = RED;
   playButton.buttonScaleMin = quitButton.buttonScaleMin = 0.9f;
   playButton.buttonScaleMax = quitButton.buttonScaleMax = 1.1f;

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
   // Move camera
   float t = GetTime() * 0.1f;
   camera.position = {-0.5f + sinf(t) * 3.0f, -8.0f + cosf(t * 0.7f) * 1.5f, -13.0f};

   // Update buttons
   playButton.update(dt);
   quitButton.update(dt);

   if (playButton.clicked) {
      playingALevel = true;
      quitState = true;
   }

   if (quitButton.clicked) {
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

   drawTextResponsive(getFont("protest-strike"), titlePosRatio.x, titlePosRatio.y, "FACTORY SIM", fontTitle, RED);
   playButton.draw();
   quitButton.draw();
}

// Change

State *MenuState::change() {
   if (playingALevel) {
      return new MainGameState(GridSettings{5000, 5000, 32});
   }
   return nullptr;
}
