// Creator: Jeremi Toroj
// Date: 19.01.2024


#include <iostream>
#include "GameOfLife.hpp"
#include <thread>
#include <chrono>
#include <fstream>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <size>" << " <starts_pairs_file>" << std::endl;
        return 1;
    }

    GameOfLife game(std::stoi(argv[1]));

    std::vector<std::pair<int, int>> start_cells;

    std::ifstream file(argv[2]);

    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    int n_pairs;
    file >> n_pairs;
    int x, y;
    while(n_pairs--)
    {
        file >> x >> y;
        start_cells.push_back(std::make_pair(x, y));
    }

    game.Initial_state(start_cells);
    bool running = true;

    while (running)
    {
        std::cout << game.GetBoardAsString() << std::endl;
        game.NextGeneration();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}