#include "tiktaktoe.cpp"

int main(int argc, char *argv[])
{
    int dem;
    std::cout << " Enter dimention of grid between 2 and 1000: ";
    std::cin >> dem;
    std::cout << std::endl;
    if (dem > 1000)
    {
        std::cout << " Too big, please add a dimention lower than 1000";
        // throw an error
    }
    if (dem < 2)
    {
        std::cout << "You need at least dimention 2 to make a grid ";
        // throw an error
    }

    TikTac::TikTacToeGrid game_start = TikTac::TikTacToeGrid(dem);
    int turns = 0;
    // Get input from both players
    game_start.PrintGrid();
    while (turns < dem * dem)
    {
        int position = -1;
        ++turns;
        do
        {
            std::cout << " Player 'O' pick your position from the grid: ";
            std::cin >> position;
            std::cout << std::endl;
        } while (!game_start.AddOToGrid(position));
        if (game_start.is_winning_position("O", position))
        {
            game_start.PrintGrid();
            break;
        }

        ++turns;
        do
        {
            std::cout << " Player 'X' pick your position from the grid: ";
            std::cin >> position;
            std::cout << std::endl;
        } while (!game_start.AddXToGrid(position) && turns < dem * dem);
        // if (game_start.)
        if (game_start.is_winning_position("X", position))
        {
            game_start.PrintGrid();
            break;
        }

        game_start.PrintGrid();
    }
}