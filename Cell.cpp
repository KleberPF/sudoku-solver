#include "Cell.h"

#include <QMouseEvent>

using namespace Qt::Literals::StringLiterals;

Cell::Cell()
    : QFrame()
{
    this->setFrameStyle(QFrame::Box);
    this->setFixedSize(30, 30);

    this->layout_ = new QHBoxLayout;
    this->layout_->setAlignment(Qt::AlignCenter);
    this->layout_->setContentsMargins(0, 0, 0, 0);

    this->value_ = new QLabel();
    this->fontSize_ = "20px";
    this->background_ = "none";
    this->updateStyle();

    this->layout_->addWidget(this->value_);
    this->setLayout(this->layout_);
}

QString Cell::getValue()
{
    return this->value_->text();
}

void Cell::setValue(const QString& value)
{
    this->value_->setText(value);
}

void Cell::setSelected(bool selected)
{
    if (selected)
    {
        this->background_ = "#ACCEF7";
    }
    else
    {
        this->background_ = "none";
    }

    this->updateStyle();
}

void Cell::setNumberColor(const QString& colorHex)
{
    this->color_ = colorHex;
    this->updateStyle();
}

void Cell::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit this->leftMousePressed();
    }
}

void Cell::updateStyle()
{
    this->setStyleSheet(uR"(
        * {
            font-size: %1;
            background: %2;
        }
        QLabel { color: %3 }
    )"_s.arg(this->fontSize_, this->background_, this->color_));
}
