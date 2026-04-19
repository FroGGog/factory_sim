#pragma once
#include "game/state.hpp"
#include <raylib.h>

struct MenuState: public State {
   enum class Phase {title, levelSelection};

   // Default

   MenuState();

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State *change() override;

   // Members

   Camera3D camera;

   Phase phase = Phase::title;
   bool playingALevel = false;
};
