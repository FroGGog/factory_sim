#include "game/gamestate.hpp"
#include <iostream>

// MainGameState 
MainGameState::MainGameState(const GridSettings& gr_settings)
{
    m_grid = std::make_unique<Grid>(gr_settings);
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
        for(const auto& row : m_grid->getGrid())
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
}


void MainGameState::fixedUpdate()
{

}

void MainGameState::render()
{
    m_grid->render();
}

State *MainGameState::change()
{
   return nullptr;
}

