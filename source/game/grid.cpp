#include "game/grid.hpp"

size_t Entity::m_global_id = 0;

Entity::Entity() : m_id(m_global_id) 
{ 
    m_global_id++;
}

// Grid class
Grid::Grid(const GridSettings& settings)
{   
    // x = 1500 y = 150
    m_collumns = static_cast<int>(settings.m_x / settings.m_tileSize); 
    m_rows = static_cast<int>(settings.m_y / settings.m_tileSize);

    m_tiles.resize(m_rows);

    for(size_t row = 0; row < m_rows; row++)
    {
        m_tiles[row].resize(m_collumns);
        for(size_t col = 0; col < m_collumns; col++)
        {
            Tile temp;
            temp.type = TileType::NONE;
            temp.m_colliderbox = Rectangle{static_cast<float>(settings.m_tileSize * col),
                static_cast<float>(settings.m_tileSize * row), 
                static_cast<float>(settings.m_tileSize), 
                static_cast<float>(settings.m_tileSize)};
            m_tiles[row][col] = temp;
        }
    }
}

void Grid::render()
{
    for(const auto& row : m_tiles)
    {
        for(const auto& tile : row)
        {
            if(getEntity(tile.entity_id) != nullptr)
            {
                const Entity& ent = *getEntity(tile.entity_id);
                Vector2 pos = { tile.m_colliderbox.x, tile.m_colliderbox.y };
                drawTexture(ent.m_texture, Vector2{pos}, Vector2{static_cast<float>(ent.m_texture.width),
                    static_cast<float>(ent.m_texture.height)});
            }
            else
            {
                if(tile.type == TileType::NONE || tile.type == TileType::GHOST)
                {
                    DrawRectangleLines(tile.m_colliderbox.x, tile.m_colliderbox.y, 32, 32, WHITE);
                }
            }
        }
    }
}



void Grid::placeEntity(int x, int y, Entity ent)
{
    if(canPlaceEntity(x, y))
    {
        m_tiles[y][x].type = TileType::ROOT;
        m_entities.push_back(std::move(ent));

        size_t new_id = m_entities.back().m_id;
        m_tiles[y][x].entity_id = new_id;
    }
}


bool Grid::canPlaceEntity(int x, int y)
{
    if( y < 0 || y >= static_cast<int>(m_tiles.size()) ||
        x < 0 || x >= static_cast<int>(m_tiles[y].size()))
    {
        return false;
    }
    return m_tiles[y][x].type == TileType::NONE;
}

const Entity* Grid::getEntity(size_t id)
{
    // TODO: if vec realoc memory pointer will point on trash, change it
    for(const auto& entity : m_entities)
    {
        if(entity.m_id == id)
        {
            return &entity;
        }
    }
    return nullptr;
}

std::span<Entity> Grid::getEntities()
{
    std::span<Entity> entities(m_entities);
    return entities;
}

const std::vector<std::vector<Tile>>& Grid::getTiles()
{
    return m_tiles;
}

size_t Grid::getRowCount()
{
    return m_rows;
}

size_t Grid::getCollumnCount()
{
    return m_collumns;
}
