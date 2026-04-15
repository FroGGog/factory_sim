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
            Cell temp;
            temp.m_bounds = Rectangle{static_cast<float>(col * settings.m_cellSize), 
                static_cast<float>(row * settings.m_cellSize),
                static_cast<float>(settings.m_cellSize), 
                static_cast<float>(settings.m_cellSize)};
            temp.m_type = getRandomCellType();
            m_grid[row].push_back(temp);
        }
    }
}

void Grid::render()
{
    for(const auto& row : m_grid)
    {
        for(const auto& cell : row)
        {
            Color cellColor;
            switch (cell.m_type)
            {
            case CellType::EMPTY:
                cellColor = {0, 0, 0, 255};
                break;
            case CellType::FLOOR:
                cellColor = {189, 168, 117, 255};
                break;
            case CellType::RESOURCE:
                cellColor = {246, 247, 161, 255};
                break;
            case CellType::ROCK:
                cellColor = {76, 77, 71, 255};
                break;
            default:
                cellColor = {255, 255, 255, 255};
                break;
            }
            DrawRectangleRec(cell.m_bounds, cellColor);
            DrawRectangleLinesEx(cell.m_bounds, 0.5f, WHITE);
        }
    }
}

std::vector<std::vector<Cell>> &Grid::getGrid()
{
    return m_grid;
}

Cell &Grid::getCell(int row, int col)
{
    return m_grid.at(row).at(col);
}

CellType Grid::getRandomCellType()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);

    switch (dis(gen))
    {
    case 0: 
        return CellType::EMPTY;
    case 1: 
        return CellType::FLOOR;
    case 2: 
        return CellType::ROCK;
    case 3: 
        return CellType::RESOURCE;
    default: 
        return CellType::EMPTY;
    }
}
