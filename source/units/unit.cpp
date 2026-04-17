#include "units/unit.hpp"
#include "mngr/asset.hpp"
#include "util/draw.hpp"
#include <raymath.h>

Unit::Unit(UnitType type, const std::string &textureName, float maxHealth, float regenerationRate, Vector2 size)
   : c_type(type), c_texture(getTexture(textureName)), c_maxHealth(maxHealth),
   c_regenerationRate(regenerationRate), c_size(size)
{
   m_health = c_maxHealth;
}

// update units

void Unit::update() {
   if (m_isPlayerControlling) {
      updatePlayerMovement();
   } else {
      updateBotMovement();
   }
}

void Unit::updatePlayerMovement() {
   float directionX = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
   float directionY = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
   Vector2 normalized = Vector2Normalize({directionX, directionY});
   m_position = Vector2Add(m_position, normalized);
}

void Unit::updateBotMovement() {
   float directionX = 0.5f; // calculate somehow later, for now testing
   float directionY = 0.0f;
   Vector2 normalized = Vector2Normalize({directionX, directionY});
   m_position = Vector2Add(m_position, normalized);
}

// render units

void Unit::render() {
   drawTexture(c_texture, m_position, c_size);
}

void Unit::setWhetherThePlayerIsControlling(bool isControlling) {
   m_isPlayerControlling = isControlling;
}

bool Unit::isUnderControl() {
   return m_isPlayerControlling;
}
