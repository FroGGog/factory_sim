#include "game/grid.hpp"

size_t Entity::m_global_id = 0;


Entity::Entity() : m_id(m_global_id) 
{ 
    m_global_id++; 
}

// Grid class

Grid::Grid(const GridSettings& settings)
    :m_small_texture(getTexture("test_large"))
{   
    // x = 1500 y = 150
    m_collumns = static_cast<int>(settings.m_x / settings.m_tileSize); 
    m_rows = static_cast<int>(settings.m_y / settings.m_tileSize);

    m_big_texture = getTexture("test_small");

    m_tiles.resize(m_rows);

    for(size_t row = 0; row < m_rows; row++)
    {
        m_tiles[row].reserve(m_collumns);
        for(size_t col = 0; col < m_collumns; col++)
        {
            Entity temp;
            temp.m_texture = m_small_texture;
            temp.m_size = Vector2{64, 64};
            placeEntity(col, row, temp);
            m_entities.push_back(temp);
        }
    }
}

void Grid::render()
{
    for(const auto& row : m_tiles)
    {
        for(const auto& tile : row)
        {
            const Entity& ent = getEntity(tile.entity_id);
            drawTexture(ent.m_texture, Vector2{tile.root_pos.value_or(Vector2{0,0}).x * 64, tile.root_pos.value_or(Vector2{0,0}).y *64}, 
                Vector2{static_cast<float>(ent.m_texture.width),
                static_cast<float>(ent.m_texture.height)});
        }
        
    }
}


void Grid::placeEntity(int x, int y, Entity ent)
{
    Tile root;
    root.entity_id = ent.m_id;
    root.type = TileType::ROOT;
    root.root_pos = Vector2{static_cast<float>(x), static_cast<float>(y)};
    m_tiles.at(y).push_back(root);
}


bool Grid::canPlaceEntity()
{
    return false;
}

const Entity& Grid::getEntity(size_t id)
{
    for(const auto& entity : m_entities)
    {
        if(entity.m_id == id)
        {
            return entity;
        }
    }
}
