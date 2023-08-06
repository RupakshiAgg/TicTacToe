#include <iostream>
#include <unordered_map>

namespace TikTac
{
  class TikTacToeGrid
  {
  public:
    // 2 player game, infinite board
    TikTacToeGrid(int dem)
    {
      grid_dimention = dem;
    };

    ~TikTacToeGrid() = default;
    void PrintGrid();
    bool AddXToGrid(int pos);
    bool AddOToGrid(int pos);
    bool is_player_winner(std::string player);

  private:
    int grid_dimention;
    std::unordered_map<int, std::string> position;
  };
} // TikTac namespace