#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QApplication>
#include <QDebug>
//#include "songlist.h"

#define MAXFIXTUREONSTAGE 2048

// glabal vars
struct Step{
    int cueID;
    int stepID;
    QString Name;
    float Fade;
    float Duration;
    float TimeCode;
};

struct Cue{
    int cueID;
    QString cueName;
    float timeCode;
    QVector<Step> cueSteps;
    void addStep(Step &mStep){
        cueSteps.push_back(mStep);
    }

};


struct Fixture_Funcs{
    unsigned char Min, Max;
    int MinRange, MaxRange;
};

struct FixtureChannelFcn{
    int ID;
    QString Name;
    int Func;
    QVector<Fixture_Funcs> FuncVec;
};

struct Manufacturer {
    int ID;
    QString Name;

};

struct FixtureModes {
    int ID;
    QString Name;
    QVector<FixtureChannelFcn> ChVec;
};

struct ShowFixtures {
    QString Mnfctr;
    QString Model;
    QString Mode;
    int ID, Universe, PanO, TiltO;
    int Quantity;
};

struct Fixtures {
    int ID;
    QString Name;
    int ManID; //Manufacturer ID
    QVector<FixtureModes> FuncModeVec;
};

struct PopUpReturn {
    QString s1, s2, s3, s4, s5;
    int Ref;
};

Q_DECLARE_METATYPE(PopUpReturn)
Q_DECLARE_METATYPE(ShowFixtures)

#endif // GLOBALDATA_H
