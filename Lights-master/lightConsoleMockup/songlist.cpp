#include "songlist.h"



songList::songList(int id, QString name, QString time):
    songID(id), songName(name) , songTimeCode(time) // initializing list
{
    nextNode = nullptr;
    SeqOrTrig = 0;
    //    Cue mCue;
    //    mCue.cueName = " Cue name";
    //    mCue.timeCode = "Timecode\n00:00:00:00";
    //    mCue.cueID = 0;
    //    cueVec.push_back(mCue);

    //    Step mStep;
    //    mStep.stepID = 0;
    //    mStep.Name = "Step Name";
    //    mStep.Fade = "Fade Time\nNs";
    //    mStep.Duration = "Duration\nNs";
    //    mStep.TimeCode = "Timecode\n00:00:00:00";
    ////    mStep.cueID = cueID;
    //    qDebug() << "cue id";
    //    cueVec.last().cueSteps.push_back(mStep);


    //    cueVec.operator[](0).cueSteps.push_back(mStep);//.addStep(mStep);
}

QString songList::getTimeCode()
{
    char buf[100];
    if((SeqOrTrig == 0) || (SeqOrTrig == 2)) sprintf(buf,"Trigger");
    if(SeqOrTrig == 1) sprintf(buf,"Time Code");
    if(SeqOrTrig == 3)
    sprintf(buf,"Time Code\n%02d:%02d:%02d:%02d", (int)TimeCode/3600,((int)TimeCode/60)%60, ((int)TimeCode)%60, (int)(TimeCode*100)%100 );
    songTimeCode = buf;
    return songTimeCode;
}


void songList::addStepInCue(int cueID, Step &mStep)
{
    //        cueVec.at(cueId).cueSteps;
    //    qDebug() << "cueID"<< cueID;
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if (cueVec.at(i).cueID == cueID)
        {
            cueVec.operator[](i).cueSteps.push_back(mStep);
            break;
        }
    }
}

QVector<Step> songList::getStepsFromCue(int cueID)
{
    //    qDebug() << " getting steps" << cueID;

    QVector<Step> mm;
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if ( cueVec.at(i).cueID == cueID)
        {
            mm = cueVec.at(i).cueSteps;
        }
    }
    return mm;

    //
}

void songList::deleteCue(int cueID)
{
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if ( cueVec.at(i).cueID == cueID)
        {
            cueVec.remove(i);
            //            cueVec.removeOne(cueVec.at(i));
        }
    }
}
void songList::deleteStepFromCue(int cueID, int stepID)
{
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if (cueVec.at(i).cueID == cueID)
        {
            for ( int j = 0 ; j < cueVec.at(i).cueSteps.size() ; j++ ){
                if (  cueVec.at(i).cueSteps.at(j).stepID == stepID ){
                    //cueVec.at(i).cueSteps
                    cueVec.operator[](i).cueSteps.remove(j);
                    //                    qDebug() << cueVec.at(i).cueSteps.at(j).stepID;
                }
            }
        }
    }
}

#include <locale.h>



//using namespace std;

void songList::editSong(QString name, float time)
{
    this->songName = name;
    this->songTimeCode = time;
    setlocale(LC_NUMERIC,"en_US");
    this->TimeCode = time;
    if(this->SeqOrTrig < 2) this->SeqOrTrig += 2;                //Signal that it is not triggerable Now
}
void songList::editCue(int cueID , Cue &mCue){
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if ( cueVec.at(i).cueID == cueID)
        {
            cueVec.replace(i, mCue);
        }
    }
}
void songList::editStep(int cueID ,int stepID ,Step &mStep){
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if (cueVec.at(i).cueID == cueID)
        {
            for ( int j = 0 ; j < cueVec.at(i).cueSteps.size() ; j++ ){
                if (  cueVec.at(i).cueSteps.at(j).stepID == stepID ){
                    //cueVec.at(i).cueSteps
                    cueVec.operator[](i).cueSteps.replace( j , mStep);
                    //                    qDebug() << cueVec.at(i).cueSteps.at(j).stepID;
                }
            }
        }
    }
}
Cue * songList::getCue(int cueID)
{
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if ( cueVec.at(i).cueID == cueID)
        {
            qDebug() << cueVec.at(i).cueName;
            qDebug() << cueVec.at(i).timeCode;
            return (Cue *) & cueVec.at(i);
            //            cueVec.removeOne(cueVec.at(i));
        }
    }
    return 0;
}
Cue songList::getCueItem(int cueID)
{
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if ( cueVec.at(i).cueID == cueID)
        {
            qDebug() << cueVec.at(i).cueName;
            qDebug() << cueVec.at(i).timeCode;
            return cueVec.at(i);
            //            cueVec.removeOne(cueVec.at(i));
        }
    }
}
Step * songList::getStepItemFromCue(int cueID, int stepID){
    Step * S;
    //S->Name = "";
    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if (cueVec.at(i).cueID == cueID)
        {
            for ( int j = 0 ; j < cueVec.at(i).cueSteps.size() ; j++ ){
                if (  cueVec.at(i).cueSteps.at(j).stepID == stepID ){
                    //cueVec.at(i).cueSteps
                    return (Step *) &cueVec.operator[](i).cueSteps.at(j);
                    //                    qDebug() << cueVec.at(i).cueSteps.at(j).stepID;
                }
            }
        }
    }
    return S;
}

Step *  songList::getNextStepItemFromCue(int cueID, int stepID){

    for ( int i = 0 ; i < cueVec.size() ; i++) {
        if (cueVec.at(i).cueID == cueID)
        {
            //int s = cueVec.at(i).cueSteps.size();
            for ( int j = 0 ; j < cueVec.at(i).cueSteps.size() ; j++ ){
                if (  cueVec.at(i).cueSteps.at(j).stepID == stepID ){
                    //cueVec.at(i).cueSteps
                    if(j<(cueVec.at(i).cueSteps.size()-1)){
                        return (Step *) & cueVec.operator[](i).cueSteps.at(j+1);
                    } else
                        return 0;
                    //                    qDebug() << cueVec.at(i).cueSteps.at(j).stepID;
                }
            }
        }
    }
    return 0;
}
