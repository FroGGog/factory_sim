#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

constexpr float fixedUpdateDT = 1.0f / 60.0f;
constexpr float maxDT = 0.25f;

struct State {
   State() = default;
   virtual ~State() = default;

   // Virtual functions

   virtual void update() = 0;
   virtual void fixedUpdate() = 0;
   virtual void render() = 0;
   virtual State *change() = 0;

   // Update functions

   void updateStateLogic();

   // Members

   bool quitState = false;
   float accumulator = 0.0f;
   float timerDt = 0.0f;
   float dt = 0.0f;
};

#endif
