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

bool TikTac::TikTacToeGrid::check_rt_diagonal(std::string player)
{
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
      return true;
    }
    i = i + grid_dimention + 1;
    value = position.find(i);
  }

  return false;
}
bool TikTac::TikTacToeGrid::check_lt_diagonal(std::string player)
{
  int i = 0;
  int count = 0;
  int j = grid_dimention - 1;
  auto value = position.find(j);
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

      return true;
    }
    j = j + grid_dimention - 1;
    value = position.find(j);
  }
  return false;
}

bool TikTac::TikTacToeGrid::check_row(std::string player)
{
  int i = 0;
  int count;
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
        return true;
      }
    }
    i += 3;
  }
  return false;
}

bool TikTac::TikTacToeGrid::check_col(std::string player)
{
  int j;
  for (int i = 0, count = 0; i < grid_dimention; ++i)
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
        return true;
      }
      j += grid_dimention;
      col_value = position.find(j);
    }
  }
  return false;
}

// This function iterates the entire map and try to find match for a given player.
bool TikTac::TikTacToeGrid::is_player_winner(std::string player)
{
  // we will do a different search for cols, rows and diagonals
  int i = 0;
  int count = 0;
  auto value = position.find(i);

  // Find consecutive match in right diagonal
  if (check_rt_diagonal(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched the right diagonal and WON THIS ROUND.\n";
    return true;
  }

  // Find consecutive match in left diagonal
  if (check_lt_diagonal(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched the lest diagonal and WON THIS ROUND.\n";
    return true;
  }

  // Find consecutive match in rows
  if (check_row(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched a row and WON THIS ROUND.\n";
    return true;
  }
  // Find consecutive match in Columns
  if (check_col(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched a column and WON THIS ROUND.\n";
    return true;
  }

  // no match
  return false;
}

// Iterates the map to find a match in either diagonal or column and row the the player's last move.
bool TikTac::TikTacToeGrid::check_row(std::string player, int pos)
{
  // Match Latest position and Left of latest position
  int lt_pos = pos;
  bool lt_row_match = false;
  int count = 0; // keeps track of number of consequtive matches
  while (true)
  {
    auto get_value = position.find(lt_pos);
    if (get_value == position.end())
    {
      break;
    }
    if (get_value->second == player)
    {
      count++;
    }
    if (lt_pos % grid_dimention == 0)
    {
      // First value of the row is the last element we need to check for left side
      break;
    }
    lt_pos--;
  }
  // Match right of latest position
  int rt_pos = pos + 1;
  while (rt_pos % grid_dimention != 0)
  {
    auto get_value = position.find(rt_pos);
    if (get_value == position.end())
    {
      break;
    }
    if (get_value->second == player)
    {
      count++;
    }
    rt_pos++;
  }

  if (count == grid_dimention)
  {
    return true;
  }
  return false;
}

bool TikTac::TikTacToeGrid::check_col(std::string player, int pos)
{
  int up_col = pos;
  int count = 0;
  while (up_col >= 0)
  {
    auto get_value = position.find(up_col);
    if (get_value == position.end())
    {
      break;
    }
    if (get_value->second == player)
    {
      count++;
    }
    up_col -= grid_dimention;
  }

  int down_col = pos + grid_dimention;
  while (down_col < grid_dimention * grid_dimention)
  {
    auto get_value = position.find(down_col);
    if (get_value == position.end())
    {
      break;
    }
    if (get_value->second == player)
    {
      count++;
    }
    down_col += grid_dimention;
  }
  if (count == grid_dimention)
  {
    return true;
  }
  return false;
}

// TODO: Only search diagonals if the current entry can be in a diagonal.
bool TikTac::TikTacToeGrid::is_winning_position(std::string player, int pos)
{

  // Always checks if there's a match in either diagonal
  if (check_rt_diagonal(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched the right diagonal and WON THIS ROUND.\n";
    return true;
  }

  if (check_lt_diagonal(player))
  {
    std::cout << "WINNER!! Player '" << player << "' matched the lest diagonal and WON THIS ROUND.\n";
    return true;
  }

  // Do a different search for rows and column based on the player latest entry
  if (check_row(player, pos))
  {
    std::cout << "WINNER!! Player '" << player << "' matched a row and WON THIS ROUND.\n";
    return true;
  }
  // Match Col
  if (check_col(player, pos))
  {
    std::cout << "WINNER!! Player '" << player << "' matched a column and WON THIS ROUND.\n";
    return true;
  }
  return false;
}