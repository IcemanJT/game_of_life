// Creator: Jeremi Toroj
// Date: 2.01.2024

#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include "CursorList.hpp"
#include <vector>

class GameOfLife
{
private:
    std::vector<std::vector<bool>> board;

    CursorList<int> *cells_to_check;

    CursorList<int> *alive_cells;
    CursorList<int> *alive_next_gen;

    int size;

public:
    GameOfLife(int size);

    ~GameOfLife();

    void SetCell(int x, int y, bool value);

    bool GetCell(int x, int y);

    void AddCellsToCheck();

    int CheckNeighbours(int x, int y);

    void NextGeneration();

    void PrintBoard();
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
    cells_to_check = new CursorList<int>(size * size);
    alive_next_gen = new CursorList<int>(size * size);
}

inline GameOfLife::~GameOfLife()
{
    delete alive_cells;
}

inline void GameOfLife::SetCell(int x, int y, bool value)
{
    board[x][y] = value;
}

inline bool GameOfLife::GetCell(int x, int y)
{
    return board[x][y];
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
    cells_to_check->clear();
    // add to cells_to_check all alive cells and their neighbours
    for (int i = 0; i < alive_cells->size(); i++)
    {
        
    }
}



#endif // GAMEOFLIFE_HPP