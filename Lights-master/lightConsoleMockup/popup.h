#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QLineEdit>
#include <QKeyEvent>
#include <QVBoxLayout>
#include "shadowlib.h"
#include "fixture.h"
#include "globalData.h"
#include "ui_FixFunction.h"

class PopUp : public QDialog
{
    Q_OBJECT

    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit PopUp(int Type = 0, QDialog *parent = nullptr);
    //~PopUp(){
    //    pDiaShadow->deleteLater();
    //}
    QString mGetTimeCode();

    void mSetPlaceHolder(int pos, QString val);
    void setPopupText(int pos, const QString& text); // Setting text notification

    void rePosition(int x, int y);
    void setSize(int h, int w);

    ShadowLib * pDiaShadow;
    Ui_FixFunction * ui;
    //QPoint StartPoint;

protected:
    void paintEvent(QPaintEvent *event);    // The background will be drawn through the redraw method

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

     void keyPressEvent(QKeyEvent *event);
     void keyReleaseEvent(QKeyEvent *event);


public slots:
    void show();                            /* own widget displaying method
                                             * It is necessary to pre-animation settings
                                               * */
    void setInputVal_SLOT();
    void SelectionEntered(void);

private slots:
    void hideAnimation();                   // Slot start the animation hide
    void hide();                            /* At the end of the animation, it is checked in a given slot,
                                             * Does the widget visible, or to hide
                                             * */
    void RaisePopUp();

signals:
    void valueEntered_SIGNAL(QVariant);
    //void ExtraValues(QString, QString, QString, QString);
private:
    QLabel label, label2, label3, label4, label5;
    QPushButton btn1, btn2;
    QLineEdit Input1, Input2, Input3, Input4, Input5 ;
    QHBoxLayout HLayout;
    QVBoxLayout Vlayout;
    QGridLayout layout;
    QPropertyAnimation animation;
    float popupOpacity;
    QTimer *timer;
    QString mInput;
    PopUpReturn mOutPut;
    QVariant vOut;
    QString greyInputClr = "color:white;background-color: rgb(127, 127, 127); border-style: solid;border-color: rgb(120, 120, 120);border-width: 1px;border-radius: 5px; color:rgb(255, 255, 255);";
    QString greyLblClr = "QLabel { color : rgb(50, 50, 255); background-color: rgba(1, 1, 1, 150); margin-top: 0px; margin-bottom: 0px; margin-left: 1px;border-radius: 5px; margin-right: 1px; font-weight:Normal;}";
    QString blueBtnClr = "QPushButton{color:white;background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(40, 25, 220, 255), stop:1 rgba(25, 15, 140, 255));border-style: solid;border-color: rgb(25, 15, 200);border-width: 0px;border-radius: 5px;font-size:10}";
    QString greyBtnClr = "QPushButton{color:white;background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgb(90, 90, 90);border-width: 0px;border-radius: 5px;font-size:10}";

};

#endif // POPUP_H
