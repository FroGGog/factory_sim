#include "game/gamestate.hpp"

// MainGameState 
MainGameState::MainGameState(const GridSettings& gr_settings)
    : m_grid(gr_settings), m_settings(gr_settings)
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
        Vector2 mousePos = GetMousePosition();
        
        int gridX = static_cast<int>(mousePos.x) / m_settings.m_tileSize; 
        int gridY = static_cast<int>(mousePos.y) / m_settings.m_tileSize;
        
        if (gridX >= 0 && gridX < m_grid.getCollumnCount() && gridY >= 0 && gridY < m_grid.getRowCount()) 
        {
        
            const auto& tiles = m_grid.getTiles();
            const Tile& tile = tiles[gridY][gridX];    
            
            Rectangle mouseRec = {mousePos.x, mousePos.y, 3.f, 3.f};

            if(CheckCollisionRecs(tile.m_colliderbox, mouseRec))
            {
                Entity temp;
                temp.m_colliderbox = tile.m_colliderbox;
                temp.m_texture = getTexture("test_large");
                temp.m_size = Vector2{static_cast<float>(temp.m_texture.width),
                                    static_cast<float>(temp.m_texture.height)};
                
                m_grid.placeEntity(gridX, gridY, std::move(temp)); 
                
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

