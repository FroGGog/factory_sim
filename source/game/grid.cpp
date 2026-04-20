#include "game/grid.hpp"

size_t Entity::m_global_id = 0;


Entity::Entity() : m_id(m_global_id) 
{ 
    m_global_id++; 
}

// Grid class

Grid::Grid(const GridSettings& settings)
{
    m_collumns = static_cast<int>(settings.m_x / settings.m_tileSize);
    m_rows = static_cast<int>(settings.m_y / settings.m_tileSize);

    m_big_texture = getTexture("test_large");
    m_small_texture = getTexture("text_small");

    m_tiles.resize(m_rows);

    for(size_t row = 0; row < m_rows; row++)
    {
        m_tiles[row].reserve(m_collumns);
        for(size_t col = 0; col < m_collumns; col++)
        {
            Entity temp;
            temp.m_texture = m_small_texture;
            temp.m_size = Vector2{1, 1};
            placeEntity(row, col, temp);
        }
    }
}

void Grid::render()
{
    for(const auto& entity : m_entities)
    {
        
    }
}


void Grid::placeEntity(int x, int y, Entity ent)
{
    Tile root;
    root.entity_id = ent.m_id;
    root.type = TileType::ROOT;
    root.root_pos = Vector2{static_cast<float>(x), static_cast<float>(y)};
    m_tiles.at(x).push_back(root);
}


bool Grid::canPlaceEntity()
{
    return false;
}
