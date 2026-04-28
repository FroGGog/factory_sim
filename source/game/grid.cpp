#include "game/grid.hpp"

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

// Grid class
Grid::Grid(const GridSettings& settings)
{   
    // x = 1500 y = 150
    m_collumns = static_cast<int>(settings.m_x / settings.m_tileSize); 
    m_rows = static_cast<int>(settings.m_y / settings.m_tileSize);

    m_tile_size = settings.m_tileSize;

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

    m_entities.push_back(Entity{}); // reserve ID 0 as null
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
                    static_cast<float>(ent.m_texture.height)}, WHITE);
                DrawText(TextFormat("ID%lu", tile.entity_id), tile.m_colliderbox.x, tile.m_colliderbox.y, 15, RED);
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
    if(canPlaceEntity(x, y, ent.m_texture.width, ent.m_texture.height))
    {
        m_tiles[y][x].type = TileType::ROOT;
        int tile_x_count = ent.m_texture.width / m_tile_size;
        int tile_y_count = ent.m_texture.height / m_tile_size;
        
        
        if(tile_x_count != 1 || tile_y_count != 1)
        {
            for(size_t i = y; i < y + tile_y_count; i++)
            {
                for(size_t j = x; j < x + tile_x_count; j++)
                {
                    //skip root
                    if(i == y && j == x)
                    {
                        continue;
                    }

                    if(m_tiles[i][j].type == TileType::NONE)
                    {
                        m_tiles[i][j].type = TileType::GHOST;
                        m_tiles[i][j].root_pos = Vector2{static_cast<float>(x), static_cast<float>(y)};   
                                             
                    }   
                }
            }
        }

        if (!m_available_entity_slots.empty()) {
            size_t index = m_available_entity_slots.back();
            
            m_entities[index] = ent;
            m_tiles[y][x].entity_id = index;
            m_available_entity_slots.pop_back();
        }
        else {
            m_tiles[y][x].entity_id = m_entities.size();
            m_entities.push_back(ent);
        }
    }
}

void Grid::resetTileArea(Vector2 ent_pos)
{
    
    int rootX = static_cast<int>(ent_pos.x);
    int rootY = static_cast<int>(ent_pos.y);

    if(rootX >= 0 && rootX < m_collumns && rootY >= 0 && rootY < m_rows)
    {
    
        m_tiles[rootY][rootX].type = TileType::NONE;
        m_tiles[rootY][rootX].entity_id = 0;
    }
    
    for(auto& row : m_tiles)
    {
        for(auto& tile : row)
        {
            if(tile.type == TileType::GHOST && tile.root_pos == ent_pos)
            {
                tile.type = TileType::NONE;
                tile.entity_id = 0;
            }
        }
    }
}

void Grid::removeLastAddedEntity()
{
    if(m_entities.empty())
        return;
    
    const Entity& last = m_entities.back();
    
    int gridX = static_cast<int>(last.m_colliderbox.x) / m_tile_size;
    int gridY = static_cast<int>(last.m_colliderbox.y) / m_tile_size;
    
    if(gridX >= 0 && gridX < m_collumns && gridY >= 0 && gridY < m_rows)
    {
        Vector2 rootPos = Vector2{static_cast<float>(gridX), static_cast<float>(gridY)};
        resetTileArea(rootPos);
    }
    
    m_entities.pop_back();
}

void Grid::removeEntity(int x, int y)
{
    if(x < 0 || x >= m_collumns || y < 0 || y >= m_rows)
    {
        return;
    }
    size_t entity_id = m_tiles[y][x].entity_id;
    if(entity_id == 0 || entity_id >= m_entities.size())
    {
        return;
    }
    // Delete all ghost tiles
    Vector2 ent_pos = Vector2{static_cast<float>(x), static_cast<float>(y)};    
    resetTileArea(ent_pos);

    m_entities[entity_id].m_id = 0;
    m_available_entity_slots.push_back(entity_id);

    // remove root tile
    m_tiles[y][x].entity_id = 0;
    m_tiles[y][x].type = TileType::NONE;
}


bool Grid::canPlaceEntity(int x, int y, int width, int height)
{
    // out of borders check
    if( y < 0 || y >= static_cast<int>(m_tiles.size()) ||
        x < 0 || x >= static_cast<int>(m_tiles[y].size()))
    {
        return false;
    }

    // grid border check
    if(y + (height / m_tile_size) > static_cast<int>(m_rows) ||
       x + (width / m_tile_size) > static_cast<int>(m_collumns))
    {
        return false;
    }

    for(size_t i = y; i < y + (height / m_tile_size); i++)
    {
        for(size_t j = x; j < x + (width / m_tile_size); j++)
        {
            if(m_tiles[i][j].type != TileType::NONE)
            {
                return false;
            }
        }
    }
    return true;
}

Entity* Grid::getEntity(size_t id)
{
    if (id >= m_entities.size() || id == 0) {
        return nullptr;
    }
    return &m_entities[id];
}

// TODO: for big amount of entities maybe slow, rework
// NOTE: compiler will optimize this accordingly, there's no need for that
size_t Grid::getEntityIdAt(int x, int y)
{
    if(x >= 0 && x < m_collumns && y >= 0 && y < m_rows)
    {
        return m_tiles[y][x].entity_id;
    }
    return 0;
}
std::span<Entity> Grid::getEntities()
{
    std::span<Entity> entities(m_entities);
    return entities;
}

std::vector<size_t>& Grid::getAvailableEntitySlots() {
    return m_available_entity_slots;
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
