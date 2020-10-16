#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dials.h"

#include "Programmer.h"
#include "Stage.h"
#include "QuickKeys.h"
#include "controller.h"
#include "QDebug"
#include "ui_controller.h"
#include "colorpicker.h"
#include "fixture.h"

#include "rightcontrols.h"
#include "leftcontrols.h"
#include "globalData.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void LoadFixtureWindow(void);
    void LoadProgrammerWindow(int Song, int Cue, int Step);

    QVector<ShowFixtures> ShowData;

private:
     dials * d;


    rightControls * rc;
    leftControls * lc;
    Stage * Stg;
    Ui::MainWindow *ui;
    int Wid;
protected:
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void connection_SLOT();
    void LoadHome();
    void LoadProgrammer();
    void LoadFixtureWinSlot();

private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
