// Creator: Jeremi Toroj
// Date: 19.01.2024

#include <iostream>
#include "GameOfLife.hpp"
#include <thread>
#include <chrono>
#include <fstream>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <size>"
                  << " <starts_pairs_file>" << std::endl;
        return 1;
    }

    // board size 
    GameOfLife game(std::stoi(argv[1]));

    std::vector<std::pair<int, int>> start_cells;

    // file stream to read start cells from file 
    std::ifstream file(argv[2]);

    // files open with constructor - checking if succesful
    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    // number of points
    int n_pairs;
    file >> n_pairs;

    // reading points from file
    int x, y;
    while (n_pairs--)
    {
        file >> x >> y;
        start_cells.push_back(std::make_pair(x, y));
    }

    // setting initial state
    game.Initial_state(start_cells);

    // main loop
    std::string action;
    while (std::cin >> action)
    {
        if (action == "board")
        {
            std::cout << game.GetBoardAsString() << std::endl;
            // flush to make sure python script will read it
            std::cout.flush();
        }
        else if (action == "next")
        {
            game.NextGeneration();
        }
        else
        {
            std::cout << "Unknows" << std::endl;
        }
    }

    return 0;
}