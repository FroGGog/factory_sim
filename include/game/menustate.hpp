#pragma once
#include "game/state.hpp"
#include <raylib.h>
#include <vector>

struct Star {
   Vector3 pos;
   Color color;
   float radius;
   float twinkleOffset;
};

struct MenuState: public State {
   enum class Phase {title, levelSelection};

   // Default

   MenuState();

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State *change() override;

   // Members

   std::vector<Star> stars;
   Camera3D camera;

   Phase phase = Phase::title;
   bool playingALevel = false;
};
