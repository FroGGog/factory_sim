#include "game/grid.hpp"

// Grid class
Grid::Grid(const GridSettings& settings)
{
    m_collumns = static_cast<int>(settings.m_x / settings.m_cellSize);
    m_rows = static_cast<int>(settings.m_y / settings.m_cellSize);

    m_grid.resize(m_rows);

    for(size_t row = 0; row < m_rows; row++)
    {
        m_grid[row].reserve(m_collumns);
        for(size_t col = 0; col < m_collumns; col++)
        {
            m_grid[row].push_back(Rectangle{static_cast<float>(col * settings.m_cellSize), 
                static_cast<float>(row * settings.m_cellSize),
                static_cast<float>(settings.m_cellSize), 
                static_cast<float>(settings.m_cellSize)});
        }
    }
}

void Grid::render()
{
    for(const auto& row : m_grid)
    {
        for(const auto& col : row)
        {
            DrawRectangleLinesEx(col, 1.5f, WHITE);
        }
    }
}

std::vector<std::vector<Rectangle>> &Grid::getGrid()
{
    return m_grid;
}
