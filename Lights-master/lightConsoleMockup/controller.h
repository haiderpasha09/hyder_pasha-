#ifndef controller_H
#define controller_H

#include <QWidget>
#include "colorpicker.h"
#include "setup.h"
#include "globalData.h"

namespace Ui {
class controller;
}

class controller : public QWidget
{
    Q_OBJECT

public:
    explicit controller(QWidget *parent = nullptr);
    void addGridlayout(QWidget * W);
    ~controller();

private slots:

    void FixtureWinSlot();

    void on_pbSetup_clicked();

    void on_pbProgrammer_clicked();

    void on_pbHome_clicked();
    void AddFixturesSLOT(QVariant);

private:
    Ui::controller *ui;

signals:
    void HomeButtonClicked();
    void ProgramButtonClicked();
    void AddFixtureSignal(QVariant);
    void FixtureWinSignal();

};

#endif // controller_H

