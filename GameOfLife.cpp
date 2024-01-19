// Creator: Jeremi Toroj
// Date: 19.01.2024

#include "GameOfLife.hpp"

int main()
{
    GameOfLife game(20);

    std::vector<std::pair<int, int>> pairs = {
     {1, 0},
    {2, 1},
    {0, 2},
    {1, 2},
    {2, 2}
    };

    game.Inicial_state(pairs);
    game.PrintBoard();

    for (int i = 0; i < 10; i++)
    {
        game.NextGeneration();
        game.PrintBoard();
    }

    return 0;
}