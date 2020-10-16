#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include "mbuttons.h"
#include "globalData.h"


namespace Ui {
class Setup;
}

class Setup : public QWidget
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup();

private slots:
    void on_btnFixtureSetup_clicked();
    void AddFixture_SLOT(QVariant);

signals:
    void LoadFixtureWin_Signal(void );

private:
    Ui::Setup *ui;

};

#endif // SETUP_H
