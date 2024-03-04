#ifndef CELL_H
#define CELL_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>

class Cell : public QFrame
{
    Q_OBJECT

public:
    Cell();

    QString getValue();
    void setValue(const QString& value);

    void setSelected(bool selected);
    void setNumberColor(const QString& colorHex);
signals:
    void leftMousePressed();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void updateStyle();

    QHBoxLayout* layout_;

    QLabel* value_;

    // StyleSheet related
    QString fontSize_;
    QString background_;
    QString color_;
};

#endif  // CELL_H
