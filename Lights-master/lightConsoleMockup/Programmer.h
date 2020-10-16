#ifndef PROGRAMMER_H
#define PROGRAMMER_H

//#define nullptr 0

#include <QWidget>
#include <QPushButton>
#include <QElapsedTimer>
#include <QScrollArea>
#include <QScroller>
#include <QDebug>
//#include "popup.h"
#include "mbuttons.h"
#include <QVector>
//#include <QString.h>
#include "globalData.h"
#include "songlist.h"
#include "QuickKeys.h"
#include "shadowlib.h"
#include "QJsonObject"
#include <QJsonArray>
#include <QJsonDocument>
#include "userinput.h"


namespace Ui {
class programmer;
}
class songList;
class controller;

class programmer : public QWidget
{
    Q_OBJECT

public:
    explicit programmer(QWidget *parent = 0);
    ~programmer();
    static int currentIndex; // Global

    void insertNode(const int &id, const QString &s_name, const QString &s_time);
    void deleteNode(const int &id);

    QString ConvertTimeCode(int , float);

    void saveSonList(void );
    void loadSonList(void );
    void displaySongs();
    void addSongBtns(int id , QString name , int, float time);

    void emptyCue(QLayout* layout, QLayout *layout2);



    void loadCue();
    void loadSteps();
    void loadSongs();

    void addSteps(int  ,QString  , float  , float  , float );
    void addStepButtons(Step &stp);
    void emptySteps(QLayout *layout, QLayout *layout2, QLayout *layout3, QLayout *layout4);

    void emptySongs(QLayout *layout, QLayout *layout2);

//    enum selectedType { song , cue , step }btnType;

    void editSong(int, QString);

    void setButtonType(int b){gAccess.selectedButton = b;}

    QString getButtonType(void);
    void RefreshSteps(void);
    void RefreshCues(void);

private slots:
    void slotGetNumber();           // SLOT for getting number of the dynamic buttons

    void showPopup(char * pText, char * pHolder, const char * slot);
    void showInfo(char * pText, const char * slot);
    void on_btnSongs_clicked();
    void Time_update_SLOT(QVariant vParm);
    void on_btnSeq_clicked();

    void on_btnAddSongs_clicked();

    void on_btnCountOff_clicked();

    void on_btnAddSteps_clicked();

     void addCue(int id , QString name , float time);

    void addCueButtons(Cue &mCue);


    void scrollDown_SLOT();

    void on_btnAddCue_clicked();

    void switch_cue2Step();

    void editSongName_SLOT(QVariant val);
    void editSongTime_SLOT(QVariant val);
    void editCueName_SLOT(QVariant val);
    void editCueTime_SLOT(QVariant val);

    void editStepName_SLOT(QVariant val);
    void editStepFade_SLOT(QVariant val);
    void editStepDuration_SLOT(QVariant val);
    void editStepTime_SLOT(QVariant val);
    void editSongStep_SLOT();
    void on_btnCueTitle_clicked();

    void on_btnAddSongs_windowIconTextChanged(const QString &iconText);

public slots:
    void deleteSong_SLOT();
    void addSong_SLOT(QVariant );
    void addCue_SLOT(QVariant );
    void addStep_SLOT(QVariant );

    void ShowGotFocus();
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
//    screen_3 * screen3;
    QString btnType;

    mButtons * songBtns;
    mButtons * timeCodeBtns;

    mButtons * cueBtns;
    mButtons * cueTimeCodeBtns;

    mButtons * seqBtn;
    mButtons * seqTimeCodeBtns;

    mButtons * stepName;
    mButtons * stepFade;
    mButtons * stepDuration;
    mButtons * stepTimeCode;

    PopUp * addSongPopUp;

    int currentSelected;
    mButtons *currentSelecteButton;

    //int size;
    songList * head;

    songList * currentSelectedNode;
    bool isCueSelected;


    int songID;
    int cueID;
    int stepID;
    int totalSongs;
    struct GACCESS {
        int selectedButton; //0 for song, 1 for songtime,2 for 2 cue , 3 for cuetime, etc
        int selectedSong;
        int selectedCue;
        int selectedStep;
        QSize AppSize;
    } gAccess;

    //
    int iXdeffarace = -1;
    int iYdeffarance  = -1;
    bool b_mousePressed;
    bool popUpExist = false;
    //


    Ui::programmer *ui;
    QString blueBtnClr = "QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(25, 15, 140, 255), stop:1 rgba(1, 0, 91, 255));border-style: solid;border-color: rgb(0, 0, 127);border-width: 1px;border-radius: 5px;color:white;}";
//    QString greyBtnClr = "QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgb(90, 90, 90);border-width: 1px;border-radius: 5px;color:white;}";
    QString blueBtnClrSel = "QPushButton{color:white;background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(40, 25, 220, 255), stop:1 rgba(25, 15, 140, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 1px;border-radius: 5px;font-size:10}";
    QString greyBtnClr = "QPushButton{color:white;background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width:1px;border-radius: 5px;font-size:10}";
    void editCue();
    void editStep();

};

#endif // SCREEN_1_H
