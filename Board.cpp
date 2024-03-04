#include "Board.h"

Board::Board()
{
}

bool Board::valid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!this->isValueValid(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

void Board::update(const Array2D<Cell*>& uiCells)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            auto* cell = uiCells(i, j);
            bool ok;
            this->cells_(i, j) = cell->getValue().toInt(&ok);
            if (!ok)
            {
                this->cells_(i, j) = 0;
            }
        }
    }
}

void Board::updateUiBoard(Array2D<Cell*>& uiCells)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            uiCells(i, j)->setValue(QString::number(this->cells_(i, j)));
        }
    }
}

bool Board::solve()
{
    return solveRecursive(0, 0);
}

bool Board::isBoxValid(int row, int col)
{
    std::array<bool, 9> valuesFound = {};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int value = this->cells_(row + i, col + j);
            if (value == 0)
            {
                continue;
            }
            if (valuesFound[value - 1])
            {
                return false;
            }

            valuesFound[value - 1] = true;
        }
    }

    return true;
}

bool Board::isValueValid(int row, int col)
{
    if (this->cells_(row, col) == 0)
    {
        return true;
    }

    // check row
    for (int i = 0; i < 9; i++)
    {
        if (i == col)
        {
            continue;
        }

        if (this->cells_(row, col) == this->cells_(row, i))
        {
            return false;
        }
    }

    // check column
    for (int i = 0; i < 9; i++)
    {
        if (i == row)
        {
            continue;
        }

        if (this->cells_(row, col) == this->cells_(i, col))
        {
            return false;
        }
    }

    // check box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;

    return this->isBoxValid(boxRow, boxCol);
}

bool Board::solveRecursive(int row, int col)
{
    if (col == 9)
    {
        col = 0;
        row++;
        if (row == 9)
        {
            return true;
        }
    }

    bool result = false;
    if (this->cells_(row, col) == 0)
    {
        for (int i = 1; i <= 9; i++)
        {
            this->cells_(row, col) = i;
            if (this->isValueValid(row, col))
            {
                result = this->solveRecursive(row, col + 1);
                if (result)
                {
                    break;
                }
            }
        }
        if (!result)
        {
            this->cells_(row, col) = 0;
        }
    }
    else
    {
        return this->solveRecursive(row, col + 1);
    }

    return result;
}
