#ifndef USERINPUT_H
#define USERINPUT_H

#include <QWidget>
#include <qvariant.h>
#include "globalData.h"
#include <QScrollArea>
#include "fixture.h"
#include <mbuttons.h>

namespace Ui {
class UserInput;
}

class UserInput : public QWidget
{
    Q_OBJECT

public:
    explicit UserInput(QWidget *parent = nullptr);
    ~UserInput();
    void Query(QString Txt, QString hldr, int Ref = 0);
    void Update(char * l1, char * T1, char * l2, char * T2, char * l3, char * T3, int Ref = 0);
    void Info(int Type, QString txt, int Ref = 0);
    void FixtureFunctions(int Ref = 0);
    void Option(QString Txt, QString * options, int numopt, int pRef = 0);
public slots:
    void show(void);
    void SelectionEntered(void);

private:
    Ui::UserInput *ui;
    PopUpReturn ReturnVals;
    QVariant vOut;
    int CallerRef = 0;

    QString greyInputClr = "color:white;background-color: rgb(127, 127, 127); border-style: solid;border-color: rgb(120, 120, 120);border-width: 1px;border-radius: 5px; color:rgb(255, 255, 255);";
    QString greyLblClr = "QLabel { color : rgb(50, 50, 255); background-color: rgba(1, 1, 1, 150); margin-top: 0px; margin-bottom: 0px; margin-left: 1px;border-radius: 5px; margin-right: 1px; font-weight:Normal;}";
    QString blueBtnClr = "QPushButton{color:white;background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(40, 25, 220, 255), stop:1 rgba(25, 15, 140, 255));border-style: solid;border-color: rgb(25, 15, 200);border-width: 0px;border-radius: 5px;font-size:10}";
    QString greyBtnClr = "QPushButton{color:white;background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgb(90, 90, 90);border-width: 0px;border-radius: 5px;font-size:10}";


signals:
    void valueEntered_SIGNAL(QVariant);


private slots:
    void on_pbAdd_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pbAdd2_clicked();
    void on_cbOptions_activated(const QString &arg1);
    void on_lineEdit_2_returnPressed();
    void keyPressEvent(QKeyEvent *);

};
class MyLineEditt : public QLineEdit
{
  Q_OBJECT

public:
  MyLineEditt(QWidget *parent = 0);
  ~MyLineEditt();

signals:
  void focussed(bool hasFocus);

protected:
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);
};
#endif // USERINPUT_H
