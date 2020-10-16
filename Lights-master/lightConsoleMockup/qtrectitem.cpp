//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Weffc++"
//#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtrectitem.h"

#include <cassert>
#include <sstream>
#include <QGraphicsScene>
#include <QLinearGradient>
#include <QPainter>
//#pragma GCC diagnostic pop

QtRectItem::QtRectItem(QGraphicsItem *parent)
: QGraphicsRectItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
    Width = 30;
    Height = 25;
}

QVariant QtRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        if(value == true)
        {
            // do stuff if selected
            qDebug() << QString::number(ID) + " Selected";
            selected = true;
        }
        else
        {
            // do stuff if not selected
            qDebug() << QString::number(ID) + " Unselected";
            selected = false;
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
void QtRectItem::setDetails(QString pMan, QString pModel, QString pMode)
{
    Man = pMan;
    Model = pModel;
    Mode = pMode;
}
void QtRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //Create the text
  std::stringstream s;
  //s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  s << ID;
  const std::string t = s.str();

  //Resize the rect to the text its size (using QFontMetrics to find this out)
  QFontMetrics q(painter->font());
  QPen penHText(QColor("#f0f0f0"));
  painter->setPen(penHText);
  const double width = q.horizontalAdvance(t.c_str());
  const double height = q.height();
  const QRectF text_rect(-0.5 * width, -0.5 * height, width, height);
  const double padding = 4.0;
  this->setRect(QRect(-Width/2,-padding-Height-height/2,Width, Height));

  {
    QLinearGradient g(this->rect().topLeft(),this->rect().bottomRight());
    g.setColorAt(0.0,QColor(128,128,128));
    g.setColorAt(1.0,QColor(240,240,240));
    this->setBrush(g);
  }

  //Draw the text on the drawn rectangle
  painter->drawText(text_rect,t.c_str());
  //Let QGraphicsRectItem handle the default painting
  QGraphicsRectItem::paint(painter,option,widget);


}
