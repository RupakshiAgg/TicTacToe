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
    bool is_winning_position(std::string player, int pos);

  protected:
    bool check_rt_diagonal(std::string player);
    bool check_lt_diagonal(std::string player);

    // checks all rows for a match.
    bool check_row(std::string player);

    // checks all columns for a match.
    bool check_col(std::string player);

    // check row of the player's latest move.
    bool check_row(std::string player, int pos);

    // check col  of the player's latest move.
    bool check_col(std::string player, int pos);

  private:
    int grid_dimention;
    std::unordered_map<int, std::string> position;
  };
} // TikTac namespace