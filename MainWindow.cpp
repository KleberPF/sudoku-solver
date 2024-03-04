#include "MainWindow.h"

#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

#include "Board.h"
#include "Cell.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Sudoku Solver");
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    this->mainLayout_ = new QHBoxLayout;

    this->cellsLayout_ = new QGridLayout;
    this->cellsLayout_->setSpacing(1);
    this->cellsLayout_->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    this->controlsLayout_ = new QVBoxLayout;
    this->controlsLayout_->setAlignment(Qt::AlignTop);

    auto* solveButton = new QPushButton("Solve");
    connect(solveButton, &QPushButton::clicked, this, [this] {
        this->solveSudoku();
    });
    this->controlsLayout_->addWidget(solveButton);

    auto* clearButton = new QPushButton("Clear All");
    this->controlsLayout_->addWidget(clearButton);
    connect(clearButton, &QPushButton::clicked, this, [this] {
        this->clearCells();
    });

    this->controlsContainer_ = new QWidget;
    this->controlsContainer_->setLayout(this->controlsLayout_);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            auto* cell = new Cell;
            connect(cell, &Cell::leftMousePressed, this, [this] {
                this->setSelectedCell(QObject::sender());
            });

            this->cells_(i, j) = cell;
            this->cellsLayout_->addWidget(cell, i, j);
        }
    }
    this->cellsContainer_ = new QWidget;
    this->cellsContainer_->setLayout(this->cellsLayout_);
    this->mainLayout_->addWidget(this->cellsContainer_);
    this->mainLayout_->addWidget(this->controlsContainer_);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(this->mainLayout_);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (this->selectedCell_ == nullptr || event->isAutoRepeat() ||
        ((event->key() < Qt::Key_0 || event->key() > Qt::Key_9) &&
         event->key() != Qt::Key_Backspace))
    {
        return;
    }

    if (this->solved_)
    {
        this->resetCellsColors();
        this->solved_ = false;
    }

    if (event->key() == Qt::Key_0 || event->key() == Qt::Key_Backspace)
    {
        this->selectedCell_->setValue("");
        return;
    }

    auto value = event->key() - Qt::Key_0;
    this->selectedCell_->setValue(QString::number(value));
}

void MainWindow::setSelectedCell(QObject* sender)
{
    if (this->selectedCell_ != nullptr)
    {
        this->selectedCell_->setSelected(false);
    }

    auto* cell = qobject_cast<Cell*>(sender);
    cell->setSelected(true);
    this->selectedCell_ = cell;
}

void MainWindow::solveSudoku()
{
    this->board_.update(this->cells_);

    if (!this->board_.valid())
    {
        QMessageBox msgBox(QMessageBox::Warning, this->windowTitle(),
                           "This sudoku is invalid.");
        msgBox.exec();
        return;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            auto* cell = this->cells_(i, j);
            if (cell->getValue() == "")
            {
                cell->setNumberColor("#26bf42");
            }
        }
    }

    this->board_.solve();
    this->board_.updateUiBoard(this->cells_);
    this->solved_ = true;
}

void MainWindow::clearCells()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            auto* cell = this->cells_(i, j);
            cell->setValue("");
        }
    }
}

void MainWindow::resetCellsColors()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            auto* cell = this->cells_(i, j);
            cell->setNumberColor("#000000");
        }
    }
}
