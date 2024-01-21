// Creator: Jeremi Toroj
// Date: 2.01.2024

#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include "CursorList.hpp"
#include <vector>

class GameOfLife
{
    using Pair = std::pair<int, int>;

private:
    std::vector<std::vector<bool>> board;

    CursorList<int> *dead_neighbours;
    CursorList<int> *alive_cells;

    int size;

public:
    GameOfLife(int size);

    ~GameOfLife();

    // adds dead neighbours of alive cells to list of cells to check (dead_neighbours)
    void AddCellsToCheck();

    // checks how many alive neighbours has cell with given coordinates
    int CheckNeighbours(int x, int y);

    // calculates next generation from alive cells and dead neighbours
    void NextGeneration(); 

    void PrintBoard();

    // populates board with set of start cells
    void Initial_state(std::vector<Pair> &start_cells);

    // returns board as string for python script
    std::string GetBoardAsString() const;
};

inline GameOfLife::GameOfLife(int size)
{
    this->size = size;
    board.resize(size);
    for (int i = 0; i < size; i++)
    {
        board[i].resize(size);
    }

    alive_cells = new CursorList<int>(size * size);
    dead_neighbours = new CursorList<int>(size * size);
}

inline GameOfLife::~GameOfLife()
{
    delete alive_cells;
    delete dead_neighbours;
}

inline int GameOfLife::CheckNeighbours(int x, int y)
{
    int neighbours = 0;
    for (int i = std::max(0, x - 1); i <= std::min(x + 1, size - 1); i++)
    {
        for (int j = std::max(0, y - 1); j <= std::min(y + 1, size - 1); j++)
        {
            if (i == x && j == y)
                continue;
            if (board[i][j])
                neighbours++;
            if (neighbours > 4)
                break;
        }
    }
    return neighbours;
}

inline void GameOfLife::AddCellsToCheck()
{
    dead_neighbours->clear();
    int idx = alive_cells->getHead();
    int count = 0;

    while (count < alive_cells->size())
    {

        Pair coords = alive_cells->getData(idx);
        int x = coords.first;
        int y = coords.second;

        for (int i = std::max(0, x - 1); i <= std::min(x + 1, size - 1); i++)
        {
            for (int j = std::max(0, y - 1); j <= std::min(y + 1, size - 1); j++)
            {
                if (i == x && j == y)
                    continue;
                if (dead_neighbours->find(Pair(i, j)) == -1 && !board[i][j])
                {
                    dead_neighbours->push_back(Pair(i, j));
                }
            }
        }

        idx = alive_cells->getNext(idx);
        ++count;
    }
}

inline void GameOfLife::NextGeneration()
{
    AddCellsToCheck();

    int idx = alive_cells->getHead();
    int count = 0;
    

    std::vector<Pair> to_remove;
    std::vector<Pair> to_add;

    while (count < alive_cells->size())
    {
        Pair coords = alive_cells->getData(idx);
        int x = coords.first;
        int y = coords.second;

        int neighbours = CheckNeighbours(x, y);
        if (neighbours < 2 || neighbours > 3)
        {
            to_remove.push_back(coords);
        }

        idx = alive_cells->getNext(idx);
        ++count;
    }

    count = 0;
    idx = dead_neighbours->getHead();

    while (count < dead_neighbours->size())
    {
        Pair coords = dead_neighbours->getData(idx);
        int x = coords.first;
        int y = coords.second;

        int neighbours = CheckNeighbours(x, y);
        if (neighbours == 3)
        {
            to_add.push_back(coords);
        }

        idx = dead_neighbours->getNext(idx);
        ++count;
    }


    for(auto &coords : to_add)
    {
        alive_cells->push_back(coords);
        board[coords.first][coords.second] = true;
    }
    for(auto &coords : to_remove)
    {
        alive_cells->remove(coords);
        board[coords.first][coords.second] = false;
    }
    
    to_add.clear();
    to_remove.clear();
}

inline void GameOfLife::PrintBoard()
{
    std::cout << "######" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << "|";
        for (int j = 0; j < size; j++)
        {
            std::cout << (board[i][j] ? "X" : " ") << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "######" << std::endl;
}

inline std::string GameOfLife::GetBoardAsString() const
{
    std::string result;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result += (board[i][j] ? 'X' : '.');
        }
        result += '\n';
    }
    return result;
}

inline void GameOfLife::Initial_state(std::vector<Pair> &start_cells)
{
    int v_size = start_cells.size();
    for (int i = 0; i < v_size; i++)
    {
        alive_cells->push_back(start_cells[i]);
        board[start_cells[i].first][start_cells[i].second] = true;
    }
}

#endif // GAMEOFLIFE_HPP