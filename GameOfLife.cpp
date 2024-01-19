// Creator: Jeremi Toroj
// Date: 19.01.2024

#include "GameOfLife.hpp"

int main()
{
    GameOfLife game(40);

    std::vector<std::pair<int, int>> start_pairs = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, // Initial seed
        {9, 0},
        {9, 1},
        {9, 2},
        {10, 2},
        {11, 1},
        {11, 2},
        {11, 3}, // Blinker 1
        {20, 0},
        {20, 1},
        {20, 2},
        {21, 2},
        {22, 1},
        {22, 2},
        {22, 3}, // Blinker 2
        {31, 0},
        {31, 1},
        {31, 2},
        {32, 2},
        {33, 1},
        {33, 2},
        {33, 3} // Blinker 3
        // Add more blinkers to extend the breeder if needed
    };

    game.Initial_state(start_pairs);
    game.PrintBoard();

    for (int i = 0; i < 10; i++)
    {
        game.NextGeneration();
        game.PrintBoard();
    }

    return 0;
}