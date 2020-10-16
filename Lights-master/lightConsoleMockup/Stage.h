#ifndef SCREEN_2_H
#define SCREEN_2_H

#include <QWidget>
#include <QWheelEvent>
#include <QElapsedTimer>
#include <QDebug>
#include <QTimer>
#include <fixture.h>

#include "qtrectitem.h"
#include "globalData.h"
#include "customgraphic.h"

#define MAX_NUMBER_OF_FIXTURES 300

struct StageFixture {
    QtRectItem position;
    QString Manuf, Model, Mode;
};

namespace Ui {
class Stage;
}

class Stage : public QWidget
{
    Q_OBJECT

public:
    explicit Stage(QWidget *parent = nullptr);
    ~Stage();
    void AddFixtures(QString Man, QString Modl, QString Mode, int Qantity );
    void setDialButtons (int );
    void getListDial (QString Reference);

public slots:
    void deleteObjects();
    void Dials_Changed_SLOT(int ID, int Val);

private slots:
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);
    void Timer_Slot(void );
    void AddFixturesSLOT(QVariant );

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    Ui::Stage *ui;
    void resizeEvent(QResizeEvent *event) override;

    QGraphicsScene GScene;

    int del = 0;
    int del2 = 0;
    // Declare below as class member vars and set default values as below
    qreal h11 = 1.0;
    qreal h12 = 0  ;
    qreal h21 = 1.0;
    qreal h22 = 0  ;
    QtRectItem * Fixtures[MAX_NUMBER_OF_FIXTURES] ;
    int TotFixtures = 0;
    QVector <Channel> ListFuncs;
    QString ListType;
};

#endif // SCREEN_2_H
