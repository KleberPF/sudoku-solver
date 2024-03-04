#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

#include "Array2D.h"

class Board
{
public:
    Board();

    bool valid();
    void update(const Array2D<Cell*>& uiCells);
    void updateUiBoard(Array2D<Cell*>& uiCells);
    bool solve();

private:
    bool isBoxValid(int row, int col);
    bool isValueValid(int row, int col);
    bool solveRecursive(int row, int col);

    Array2D<int> cells_ = {};
};

#endif  // BOARD_H
