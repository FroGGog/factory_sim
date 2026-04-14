#include "game/loading.hpp"
#include "mngr/asset.hpp"
#include "mngr/sound.hpp"
#include "util/draw.hpp"
#include "game/loading.hpp"
#include "game/gamestate.hpp"
// Constructors

LoadingState::LoadingState() {
   loadFont("andy", "assets/fonts/roboto-mono.ttf");
   loadTexture("loading", "assets/sprites/ui/loading.png");
}

void LoadingState::update() {
   iconRotation += dt * 360.0f;

   // Sometimes brute-forcing is better than over-engineering an automatic way to do everything
   if (loadPhase == Load::fonts) {
      loadFonts();

      loadingText = "Loading Textures... ";
      loadPhase = Load::textures;
   } else if (loadPhase == Load::textures) {
      loadTextures();

      loadingText = "Loading Shaders... ";
      loadPhase = Load::shaders;
   } else if (loadPhase == Load::shaders) {
      loadShaders();

      loadingText = "Loading Sounds... ";
      loadPhase = Load::sounds;
   } else if (loadPhase == Load::sounds) {
      loadSounds();
      loadSavedSounds();

      loadingText = "Loading Done!";
      loadPhase = Load::count;
   } else if (loadPhase == Load::count) {
      finalWaitTimer += timerDt;
      quitState = (finalWaitTimer >= 1.f);
   }
}

void LoadingState::fixedUpdate() {

}

void LoadingState::render() {
   std::string finalLoadingText = loadingText;
   if (loadPhase != Load::count) {
      finalLoadingText = loadingText + std::to_string((int)loadPhase) + "/"
         + std::to_string((int)Load::count);
   }

   Font &font = getFont("roboto-mono");
   Texture &icon = getTexture("loading");

   drawTextCentered(font, getCenterOffset({0.0f, -175.0f}), finalLoadingText.c_str(), 80);
   drawTextureCentered(icon, getScreenCenter(), {70.0f, 70.0f}, iconRotation);
}

State *LoadingState::change() {
   // add check if games is ready and etc 
   MainGameState* state = new MainGameState(GridSettings{5000, 5000, 64});
   return state;
}