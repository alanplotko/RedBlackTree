#ifndef NODEGRAPHIC_H
#define NODEGRAPHIC_H


#include <QColor>
#include <QGraphicsItem>

class NodeGraphic : public QGraphicsItem
{
public:
    NodeGraphic(const QColor &color, int x, int y, int numIn);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;


private:
    int x;
    int y;
    int numIn;
    QColor color;
    QVector<QPointF> stuff;
};

#endif // NODEGRAPHIC_H
