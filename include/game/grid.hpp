#pragma once
#include <raylib.h>
#include <vector>
#include <random>

enum class CellType {EMPTY, FLOOR, ROCK, RESOURCE};

struct Cell
{
    CellType m_type;
    Rectangle m_bounds;
};

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

    std::vector<std::vector<Cell>>& getGrid();
    Cell& getCell(int row, int col);

private:

    std::vector<std::vector<Cell>> m_grid;
    int m_rows, m_collumns;

    CellType getRandomCellType();
};