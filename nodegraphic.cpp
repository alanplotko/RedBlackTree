#include "nodegraphic.h"
#include <QtWidgets>

NodeGraphic::NodeGraphic(const QColor &color, int x, int y, int numIn)
{
    this->x = x;
    this->y = y;
    this->numIn = numIn;
    this->color = color;
    this->isLeft = isLeft;
}

QRectF NodeGraphic::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}

void NodeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(150);
    QBrush b = painter->brush();
    painter->setBrush(fillColor);
    painter->drawEllipse(13, 13, 50, 50);
    painter->setPen(Qt::black);
    painter->drawText(x, y, QString(QString::number(numIn)));
    painter->setBrush(b);
}
