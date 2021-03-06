#ifndef CUSTOMGRAPHIC_H
#define CUSTOMGRAPHIC_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>

class customGraphic : public QGraphicsView
{
  Q_OBJECT
public:
  explicit customGraphic(QWidget *parent = nullptr) : QGraphicsView(parent)
  {
    setDragMode(QGraphicsView::ScrollHandDrag);

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/my_image.png"));
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(pixmapItem);
    setScene(scene);
  }

protected Q_SLOTS:
  void wheelEvent(QWheelEvent *event)
  {
      //QPoint pd;
      //pd = event->pixelDelta();
    if(event->angleDelta().y() > 0)
      scale(1.25, 1.25);
    else
      scale(0.8, 0.8);
  }

  void keyPressEvent(QKeyEvent *event)
  {
    if(event->key() == Qt::Key_Left)
      rotate(1);
    else if(event->key() == Qt::Key_Right)
      rotate(-1);
  }
};


#endif // CUSTOMGRAPHIC_H
