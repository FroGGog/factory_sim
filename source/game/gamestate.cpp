#include "game/gamestate.hpp"

// MainGameState 
MainGameState::MainGameState(const GridSettings& gr_settings)
    : m_grid(gr_settings)
{
    m_camera.target = {0, 0};
    m_camera.offset = {0, 0};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
}

void MainGameState::update()
{
    sHandleEvents();
}

void MainGameState::sHandleEvents()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Rectangle mouseRec = Rectangle{GetMousePosition().x, GetMousePosition().y, 3.f, 3.f};
        for(const auto& row : m_grid.getGrid())
        {
            for(const auto& rec : row)
            {
                if(CheckCollisionRecs(rec,  mouseRec))
                {
                    // do collision click there
                    return;
                }
            }
        }
    }
    if(IsKeyDown(KEY_D))
    {
        m_camera.target.x += m_camera_speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_A))
    {
        m_camera.target.x -= m_camera_speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_W))
    {
        m_camera.target.y -= m_camera_speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_S))
    {
        m_camera.target.y += m_camera_speed * GetFrameTime();
    }
    
}


void MainGameState::fixedUpdate()
{

}

void MainGameState::render()
{
    BeginMode2D(m_camera);
    m_grid.render();
    EndMode2D();
}

State *MainGameState::change()
{
   return nullptr;
}

