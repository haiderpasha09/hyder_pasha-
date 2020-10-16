#ifndef QTRECTITEM_H
#define QTRECTITEM_H

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Weffc++"
//#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsRectItem>
#include "qdebug.h"
//#pragma GCC diagnostic pop

struct QtRectItem : public QGraphicsRectItem
{
      QtRectItem(QGraphicsItem *parent = 0);
    void setID(int mID){ID = mID;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void setDetails(QString pMan, QString pModel, QString pMode);

    bool selected;
    QString Man, Model, Mode;

private:
  int Width, Height;
  int ID;


};

#endif // QTRECTITEM_H
