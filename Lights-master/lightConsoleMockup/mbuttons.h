#ifndef MBUTTONS_H
#define MBUTTONS_H

#include <QPushButton>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QVector>
#include "popup.h"
#include "globalData.h"



class mButtons : public QPushButton
{
    Q_OBJECT
public:
    explicit mButtons(QWidget *parent = nullptr);
    ~mButtons();
    static int ResID;   // A static variable counter buttons rooms
    int getID();        // Function to return a local number buttons

    void setButtonType(QString type);
    QString getButtonType();

    void setID(int id);

    void setCueID(int id);
    int getCueID();

    void setStepID(int id);
    int getStepID();

private:

    // Pressing and holding for one full second constitutes a "longpress", set whatever value in milliseconds you want here.
    static const quint64 MY_LONG_PRESS_THRESHOLD = 500;
    int buttonID = 0;   // Local variable number of the button
    bool isPressed = false;

    //PopUp *popUp;
    //
    QString mSongName;
    QString mTimeCode;

    QVector<QString> songCues;

    QVector<Cue> cueVec;
    QVector<Cue> stepVec;

    QString btnType;

    int cueID;
    int stepID;



protected:
    // Declare that we are overriding QWidget's events for mouse press and release
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;

signals:
    // Our custom signal to emit once a longpress is detected.

    void mousePressedSIGNAL();
    void btnAdded_SIGNAL();
    void switchCue2Step_SIGNAL();
    void editButton_SIGNAL();

private slots:
    void setBtnVal_SLOT(QString);
    void mousePressedSLOT();


};

#endif // MBUTTONS_H
