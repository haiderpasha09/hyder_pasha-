#ifndef SONGLIST_H
#define SONGLIST_H

#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <cmath>
#include <cstdlib>


class songList
{
public:

    songList(int , QString , QString);

    QString getTimeCode();

    QString getSongName() const{
        return songName;
    };
    //QString getTimeCode() const{
    //    return songTimeCode;
    //};

    void setSongsList(int , QString , QString);

    songList *nextNode;
    friend class programmer;

    void addCue(Cue &mCue)
    {
        qDebug() << mCue.cueID;
        cueVec.push_back(mCue);
    }

    QVector<Cue> getCues(){
        return cueVec;
    }


    void addStepInCue(int cueID , Step &mStep);

    QVector<Step> getStepsFromCue(int cueID);

    void deleteCue(int cueID);
    void deleteStepFromCue(int cueID , int stepID);

    Cue getCueItem(int cueID);
    void editCue(int id, Cue &cue);

    Step * getStepItemFromCue(int cueID, int stepID);
    Step * getNextStepItemFromCue(int cueID, int stepID);
    void editStep(int cueID, int StepD, Step &mStep);
    Cue * getCue(int cueID);

private:
    int SeqOrTrig;  //Is this song has a Trigger (0) or TimeCode (1) or TriggerFixed or TimeCodeFixed(3)
    int stepID;
    int songID;
    float TimeCode = 0;
    QString songName;
    QString songTimeCode;

    QVector<Cue> cueVec;
    QVector<Step> stepVec;

    void editSong(QString name, float time);


};

#endif // SONGLIST_H
