#include "game/state.hpp"
#include "util/draw.hpp"
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

private:

    std::vector<std::vector<Rectangle>> m_grid;

    int m_rows, m_collumns;
};


struct MainGameState: public State
{

public:
   MainGameState(const GridSettings& gr_settings);
   ~MainGameState() = default;

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State* change() override;

private:

    std::unique_ptr<Grid> m_grid;

};
