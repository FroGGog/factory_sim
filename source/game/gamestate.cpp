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
        Vector2 worldPos = GetScreenToWorld2D(mousePos, m_camera);
        
        int gridX = static_cast<int>(worldPos.x) / m_settings.m_tileSize; 
        int gridY = static_cast<int>(worldPos.y) / m_settings.m_tileSize;
        
        if (gridX >= 0 && gridX < m_grid.getCollumnCount() && gridY >= 0 && gridY < m_grid.getRowCount()) 
        {
            Rectangle mouseRec = {worldPos.x, worldPos.y, 3.f, 3.f};
        
            const auto& tiles = m_grid.getTiles();
            const Tile& tile = tiles[gridY][gridX];    

            // check if collide with other entity than skip
            for(const auto& entity : m_grid.getEntities())
                {
                    if(entity.m_id != 0 && CheckCollisionRecs(entity.m_colliderbox, mouseRec))
                    {
                        std::cout << "[INFO] Can't place tile here - occupied \n";
                        return;
                    }
                }
            // after check if wants to place some ent
            if(CheckCollisionRecs(tile.m_colliderbox, mouseRec))
            {
                Entity temp;                
                temp.m_texture = getTexture("test_large");
                temp.m_size = Vector2{static_cast<float>(temp.m_texture.width),
                                    static_cast<float>(temp.m_texture.height)};
                float pixelX = gridX * m_settings.m_tileSize;
                float pixelY = gridY * m_settings.m_tileSize;
                temp.m_colliderbox = Rectangle{pixelX, pixelY, temp.m_size.x, temp.m_size.y};
                m_grid.placeEntity(gridX, gridY, std::move(temp)); 
            }
        }
    }

    // quick and dirty, we won't be needing this for long anyway
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        Vector2 worldPos = GetScreenToWorld2D(mousePos, m_camera);

        int gridX = int(worldPos.x / m_settings.m_tileSize);
        int gridY = int(worldPos.y / m_settings.m_tileSize);
        m_grid.removeEntity(gridX, gridY);
    }

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        m_grid.removeLastAddedEntity(); 
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
    DrawText(TextFormat("Empty Slots: %lu\nEntities: %lu", m_grid.getAvailableEntitySlots().size(),
        m_grid.getEntities().size()), 5, 5, 40, RED);
}

State *MainGameState::change()
{
   return nullptr;
}

