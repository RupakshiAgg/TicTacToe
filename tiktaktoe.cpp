#include "tiktaktoe.h"

void TikTac::TikTacToeGrid::PrintGrid()
{
  for (int i = 0; i < grid_dimention * grid_dimention; i += grid_dimention)
  {
    for (int j = i; j < i + grid_dimention; j++)
    {
      if (auto value = position.find(j); value != position.end())
      {
        std::cout << value->second << " | ";
      }
      else
      {
        std::cout << j << " | ";
      }
    }
    // printing needs to be better
    std::cout << "\n -------------------------- \n";
  }
}

bool TikTac::TikTacToeGrid::AddOToGrid(int pos)
{
  if (auto value = position.find(pos); value != position.end())
  {
    std::cout << "Already taken, pick an open position\n";
    return false;
  }
  position.insert({pos, "O"});
  return true;
}

bool TikTac::TikTacToeGrid::AddXToGrid(int pos)
{
  if (position.size() == grid_dimention * grid_dimention)
  {
    std::cout << "No more turns, Game Over\n";
    return false;
  }
  if (auto value = position.find(pos); value != position.end())
  {
    std::cout << "Already taken, pick an open position\n";
    return false;
  }
  position.insert({pos, "X"});
  return true;
}

// Currently this function iterates the entire position map and try to find match for a given player.
// TODO: Optamize it based on the current user input by only checking the possible matches, instead of all.
bool TikTac::TikTacToeGrid::is_player_winner(std::string player)
{
  // we will do a different search for cols, rows and diagonals
  int i = 0;
  int count = 0;
  auto value = position.find(i);

  // Find consecutive match in right diagonal
  while (value != position.end())
  {
    if (value->second != player)
    {
      break;
    }
    count++;
    if (count == grid_dimention)
    {
      std::cout << "WINNER!! Player '" << player << "' matched the right diagonal and WON THIS ROUND.\n";
      return true;
    }
    i = i + grid_dimention + 1;
    value = position.find(i);
  }

  // Find consecutive match in left diagonal
  int j = grid_dimention - 1;
  value = position.find(j);
  count = 0;
  while (value != position.end())
  {
    if (value->second != player)
    {
      break;
    }
    count++;
    if (count == grid_dimention)
    {
      std::cout << "WINNER!! Player '" << player << "' matched the lest diagonal and WON THIS ROUND.\n";
      return true;
    }
    j = j + grid_dimention - 1;
    value = position.find(j);
  }

  // Find consecutive match in rows
  i = 0;
  while (i < grid_dimention * grid_dimention)
  {
    count = 0;
    for (int j = i; j < j + grid_dimention; j++)
    {
      if (auto row_value = position.find(j); row_value == position.end() || row_value->second != player)
      {
        break;
      }
      count++;
      if (count == grid_dimention)
      {
        std::cout << "WINNER!! Player '" << player << "' matched a row and WON THIS ROUND.\n";
        return true;
      }
    }
    i += 3;
  }
  // Find consecutive match in Columns
  for (i = 0, count = 0; i < grid_dimention; ++i)
  {
    j = i;
    auto col_value = position.find(j);
    while (col_value != position.end())
    {
      if (col_value->second != player)
      {
        break;
      }
      count++;
      if (count == grid_dimention)
      {
        std::cout << "WINNER!! Player '" << player << "' matched a column and WON THIS ROUND.\n";
        return true;
      }
      j += grid_dimention;
      col_value = position.find(j);
    }
  }

  // no match
  return false;
}