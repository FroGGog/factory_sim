#include "game/loading.hpp"
#include <raylib.h>
#include <cstdlib>
#include <ctime>

constexpr int minWindowWidth  = 800;
constexpr int minWindowHeight = 600;

int main() {
   srand(time(nullptr));
   SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
   InitWindow(minWindowWidth, minWindowHeight, "factorySim");
   SetWindowMinSize(minWindowWidth, minWindowHeight);

   InitAudioDevice();
   SetExitKey(KEY_NULL);

   State *current = new LoadingState();
   
   while (!WindowShouldClose()) {
      if (current->quitState) {
         State *newState = current->change();
         delete current;
         current = newState;
      }

      if (!current) {
         break;
      }

      current->updateStateLogic();

      BeginDrawing();
         ClearBackground(BLACK);
         current->render();
      EndDrawing();
   }
   CloseWindow();
   CloseAudioDevice();
}
