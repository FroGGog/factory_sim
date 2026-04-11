#include "game/state.hpp"
#include <math.h>
#include <raylib.h>

void State::updateStateLogic() {
   timerDt = GetFrameTime();
   dt = fmin(maxDT, timerDt);

   accumulator += dt;
   while (accumulator >= fixedUpdateDT) {
      fixedUpdate();
      accumulator -= fixedUpdateDT;
   }
   update();
}
