// Creator: Jeremi Toroj
// Date: 2.01.2024

#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include "CursorList.hpp"

template<class N>
class GameOfLife {
private:

    CursorList<CursorList<bool>>** board;

public:

    GameOfLife(int size);

    ~GameOfLife();

    bool CheckNeighbours(int x, int y);

    void NextGeneration();

    void PrintBoard();

    void SetCell(int x, int y, bool value);

    bool GetCell(int x, int y);
    

};


#endif //GAMEOFLIFE_HPP