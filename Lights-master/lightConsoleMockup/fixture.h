#ifndef FIXTURE_H
#define FIXTURE_H

#include <QWidget>
#include <QResizeEvent>
#include <qdebug.h>
#include "QJsonObject"
#include <QJsonArray>
#include <QJsonDocument>
#include <mbuttons.h>
#include "userinput.h"
#include "globalData.h"

const QString FuncGroup[] = {"Dimmer","Position","Color","Gobo","Lens","Control"};
const QString blueBtnClr = "QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(25, 15, 140, 255), stop:1 rgba(1, 0, 91, 255));border-style: solid;border-color: rgb(0, 0, 127);border-width: 1px;border-radius: 5px;color:white;}";
const QString blueBtnClrSel = "QPushButton{color:white;background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(40, 25, 220, 255), stop:1 rgba(25, 15, 140, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 1px;border-radius: 5px;font-size:10}";

enum FixParam {fpManufacturer, fpModel, fpMode, fpChannel, fpFunction};

struct FixtureFuncs{
    QString GroupName;
    QVector<QString> Name;
};
struct Function {
    QString Name;
    int Min, Max;
    double Start, Stop;
};
struct Channel{
    QString name;
    QString Type;
    QVector<Function> FuncVec;
};
struct Mode {
    QString Name;
    QVector <Channel> ChannelVec;
};
struct Model {
    QString Name;
    QVector<Mode> ModeVec;
};
struct Manufactur {
    QString Name;
    QVector<Model> ModelVec;
};

namespace Ui {
class Fixture;
}

class Fixture : public QWidget
{
    Q_OBJECT

public:
    explicit Fixture(QWidget *parent = nullptr);
    ~Fixture();
    static QVector <Channel> GetChannel(QString Man, QString Model, QString Mode);

private slots:
    //void on_pbCreateNew_clicked();

    void Button_Click(void);
    void DeleteButton(void);
    void FixtureParams_SLOT(QVariant );
    void on_pbCreateNew_3_clicked();
    void ReceivePopUpManu(QVariant);
    void ReceivePopUpFunc(QVariant);
    void on_pbEditProfile_3_clicked();

    void on_btnAddChannel_clicked();
    void addChannel_SLOT(QVariant);

    void on_btnAddFunction_clicked();

    void on_pbPatch_3_clicked();

    void on_pbPatch_5_clicked();

    void on_pbMode_clicked();

    void on_pbQuantity_clicked();

    void on_pbUniverse_clicked();

    void on_pbAddress_clicked();

    void on_pbFixtureID_clicked();

    void on_pbPatchFix_clicked();

private:
    Ui::Fixture *ui;
    void resizeEvent(QResizeEvent *event) override;
    void saveFunctionList(void );
    void LoadFunctionList(void );
    void saveFixtureList(void );
    void loadFixtureList(void );
    void RefreshScreen(void );
    void AddButtonToScrollArea(int ID, QString Text, QString Style, QString Type, int height, QLayout * ui_scrArea, const char * SlotFunc);
    void RemoveButtonfromScrollArea(QLayout * ui_scrArea);
    void UpdateModel(QString ManuName, QString ModelName, QString ModeName, QString ChanName,
                QString FuncName, QString FuncMinVal, QString FuncMaxVal, QString FuncMinRng, QString FuncMaxRng );
    void UpdateFixtureData(FixParam Parm, QString Val1, QString Val2 = "", QString Val3 = "", QString Val4 = "", QString Val5 = "" );
    void showPopup(char * l1, char * T1, char * l2, char * p2, char * l3, char * p3,  QPoint fCorner, QPoint sCorner);
    void HiliteButtoninScrollArea(int ID, QString Norm, QString Highlite, QLayout * ui_scrArea);
    void InsertManModel(QString Man, QString Model, uint Mode);

    int SelectedMan, SelectedModel, SelectedMode, SelectedChan, SelectedFunction;
    QString SelectedButton;
    struct PatchData {
        QString Mode;
        int Quantity, Universe, Address, FixID;
    }patchData;
    int DataVals = 0;
signals:
    void AddFixturesSIGNAL(QVariant);
};

#endif // FIXTURE_H
