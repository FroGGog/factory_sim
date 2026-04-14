#pragma once
#include "game/state.hpp"
#include "game/grid.hpp"

// TODO: after all we will use this class for world generation and other stuff
struct MainGameState: public State
{

public:
   MainGameState(const GridSettings& gr_settings);
   ~MainGameState() = default;

    void sHandleEvents();

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State* change() override;

private:

    Grid m_grid;

    Camera2D m_camera;
    float m_camera_speed = 100.f;

};
