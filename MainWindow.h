#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>

#include "Board.h"
#include "Cell.h"

#include "Array2D.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setSelectedCell(QObject* sender);

    void solveSudoku();
    void clearCells();
    void resetCellsColors();

    QHBoxLayout* mainLayout_;
    QGridLayout* cellsLayout_;
    QVBoxLayout* controlsLayout_;

    QWidget* controlsContainer_;
    QWidget* cellsContainer_;

    // This object holds the UI sudoku cells
    Array2D<Cell*> cells_;
    // This object holds the actual board with
    // the values. Note that they aren't always
    // in sync (see Board::update and Board::updateUiBoard)
    Board board_;

    Cell* selectedCell_ = nullptr;

    bool solved_ = false;
};
#endif  // MAINWINDOW_H
