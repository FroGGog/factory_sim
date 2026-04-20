#pragma once
#include <raylib.h>
#include <vector>
#include <random>

#include "../include/util/draw.hpp"
#include "../include/mngr/asset.hpp"


enum class TileType {NONE, ROOT, GHOST};

// for testing
struct Entity
{
    Entity();

    static size_t m_global_id;
    size_t m_id;
    Vector2 m_size;
    Texture m_texture;
};

struct Tile
{
    TileType type;
    size_t entity_id;
    std::optional<Vector2> root_pos;
};

/// @brief 1) m_x - x size of grid; 2) m_y - y size of grid; 3) m_cellSize - size of one cell in grid
struct GridSettings
{
    int m_x;
    int m_y;
    int m_tileSize;
};

class Grid 
{
public:
    Grid(const GridSettings& settings);

    void render();

    void placeEntity(int x, int y, Entity ent);

private:

    std::vector<std::vector<Tile>> m_tiles;
    std::vector<Entity> m_entities;
    Texture2D m_small_texture;
    Texture2D m_big_texture;

    int m_rows, m_collumns;

    bool canPlaceEntity();
};