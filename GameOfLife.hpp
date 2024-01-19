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

    void AddCellsToCheck();

    int CheckNeighbours(int x, int y);

    void NextGeneration(); // <- fix

    void PrintBoard();

    void Initial_state(std::vector<Pair> &start_cells);

    std::vector<std::vector<bool>> getBoard() { return board; }
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

    std::vector<Pair> to_remove;
    std::vector<Pair> to_add;

    int idx = dead_neighbours->getHead();
    int count = 0;

    while (count < dead_neighbours->size())
    {
        Pair coords = dead_neighbours->getData(idx);
        int x = coords.first;
        int y = coords.second;

        int neighbours = CheckNeighbours(x, y);
        if (neighbours == 3)
        {
            alive_cells->push_back(coords);
            to_add.push_back(coords);
        }

        idx = dead_neighbours->getNext(idx);
        ++count;
    }

    count = 0;
    idx = alive_cells->getHead();

    while (count < alive_cells->size())
    {
        Pair coords = alive_cells->getData(idx);
        int x = coords.first;
        int y = coords.second;

        int neighbours = CheckNeighbours(x, y);
        if (neighbours < 2 || neighbours > 3)
        {
            alive_cells->remove(coords);
            to_remove.push_back(coords);
        }

        idx = alive_cells->getNext(idx);
        ++count;
    }

    int v_size = to_remove.size();
    for (int i = 0; i < v_size; i++)
    {
        board[to_remove[i].first][to_remove[i].second] = false;
    }

    v_size = to_add.size();
    for (int i = 0; i < v_size; i++)
    {
        board[to_add[i].first][to_add[i].second] = true;
    }

    dead_neighbours->clear();
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