#ifndef UNITS_UNIT_HPP
#define UNITS_UNIT_HPP

#include <raylib.h>
#include <string>

enum class UnitType: char {
   // temporary
   alpha, beta, charlie, delta, echo
};

/// @brief configuration members start with c_ whereas regular members start with m_.
/// configuration members are set once.
class Unit
{
public:
   Unit(UnitType type, const std::string &textureName, float maxHealth, float regenerationRate, Vector2 size);
   ~Unit() = default;

   void update();
   void render();

   void setWhetherThePlayerIsControlling(bool isControlling);
   bool isUnderControl();

private:

   void updatePlayerMovement();
   void updateBotMovement();

   UnitType c_type;
   Texture2D c_texture;
   float c_maxHealth;
   float c_regenerationRate;
   Vector2 c_size;

   Vector2 m_position = {0, 0};
   float m_health = 0;
   bool m_isPlayerControlling = false;
};

#endif
