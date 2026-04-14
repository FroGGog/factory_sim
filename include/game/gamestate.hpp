#include "game/state.hpp"
#include "util/draw.hpp"
#include "game/grid.hpp"
#include <vector>

struct MainGameState: public State
{

public:
   MainGameState(const GridSettings& gr_settings);
   ~MainGameState() = default;

    void sHandleEvents();

   void update() override;
   void fixedUpdate() override;
   void render() override;
   State* change() override;

private:

    std::unique_ptr<Grid> m_grid;

};
