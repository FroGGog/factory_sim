#ifndef GAME_LOADINGSTATE_HPP
#define GAME_LOADINGSTATE_HPP

#include "game/state.hpp"
#include <string>

// Loading state

struct LoadingState: public State {
   enum class Load { fonts, textures, shaders, sounds, count };

   // Constructors

   LoadingState();
   ~LoadingState() = default;

   // Functions

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State* change() override;

   // Members

   std::string loadingText;
   Load loadPhase = Load::fonts;

   float finalWaitTimer = 0.0f;
   float iconRotation = 0.0f;
};

#endif
