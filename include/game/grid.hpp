#pragma once
#include <raylib.h>
#include <vector>
#include <random>
#include <iostream>
#include <span>

#include "../include/util/draw.hpp"
#include "../include/mngr/asset.hpp"

enum class TileType {NONE, ROOT, GHOST};

void printTileType(TileType type);
// for testing
struct Entity
{
    Entity();

    static size_t m_global_id;
    size_t m_id;
    Vector2 m_size;
    Texture m_texture;
    Rectangle m_colliderbox;
};

/// @brief by default tile type is NONE 
struct Tile
{
    TileType type = TileType::NONE;
    size_t entity_id;
    std::optional<Vector2> root_pos;
    Rectangle m_colliderbox;
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

    const Entity* getEntity(size_t id);

    std::span<Entity> getEntities();
    const std::vector<std::vector<Tile>>& getTiles();

    size_t getRowCount();
    size_t getCollumnCount();

    void placeEntity(int x, int y, Entity ent);

private:

    std::vector<std::vector<Tile>> m_tiles;
    std::vector<Entity> m_entities;

    int m_rows, m_collumns, m_tile_size;

    bool canPlaceEntity(int x, int y, int width, int height);

    void printNotNoneTiles();
};