#pragma once
#include <raylib.h>
#include <vector>

/// @brief 1) m_x - x size of grid; 2) m_y - y size of grid; 3) m_cellSize - size of one cell in grid
struct GridSettings
{
    int m_x;
    int m_y;
    int m_cellSize;
};

class Grid 
{
public:
    Grid(const GridSettings& settings);

    void render();

    std::vector<std::vector<Rectangle>>& getGrid();

private:

    std::vector<std::vector<Rectangle>> m_grid;

    int m_rows, m_collumns;
};