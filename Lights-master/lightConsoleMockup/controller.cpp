#include "controller.h"
#include "ui_controller.h"

controller::controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);
    ColorPicker * Cp = new ColorPicker;
    //screen_1 * s1 = new screen_1;
    QHBoxLayout *BHLay = new QHBoxLayout;
        BHLay->addWidget(Cp);
        ui->MainWin->setLayout(BHLay);
        BHLay->setContentsMargins(0,0,2,0);
        ui->MainWin->show();
}

controller::~controller()
{
    delete ui;
}

void controller::addGridlayout(QWidget * W)
{
//    QLayoutItem *child;
//    while ((child = ui->gridLayout_2->layout()->takeAt(0)) != 0)
//    {
//        delete child;
//    }
//
//    ui->gridLayout_2->layout()->addWidget(W);

}




void controller::FixtureWinSlot(void ){
    emit FixtureWinSignal();

}


void controller::on_pbSetup_clicked()
{
    ui->textEdit->setText(ui->pbSetup->text());

    Setup * Cp = new Setup;
    //screen_1 * s1 = new screen_1;
    delete ui->MainWin->layout()->widget();
    delete ui->MainWin->layout();
    QHBoxLayout *BHLay = new QHBoxLayout;
        BHLay->addWidget(Cp);
        ui->MainWin->setLayout(BHLay);
        BHLay->setContentsMargins(0,0,0,0);
        ui->MainWin->show();
        connect(Cp, SIGNAL(LoadFixtureWin_Signal()), this, SLOT(FixtureWinSlot()));
        connect(this, SIGNAL(AddFixtureSignal(QVariant)), Cp, SLOT(AddFixture_SLOT(QVariant)));
}
void controller::AddFixturesSLOT(QVariant vParm){
    //ShowFixtures sfData;
    emit AddFixtureSignal(vParm);
}
void controller::on_pbProgrammer_clicked()
{
    ui->textEdit->setText(ui->pbProgrammer->text());
    ColorPicker * Cp = new ColorPicker;
    //screen_1 * s1 = new screen_1;
    //ui->MainWin->layout()->widget()->hide();
    delete ui->MainWin->layout()->widget();
    delete ui->MainWin->layout();
    QHBoxLayout *BHLay = new QHBoxLayout;
        BHLay->addWidget(Cp);
        ui->MainWin->setLayout(BHLay);
        BHLay->setContentsMargins(0,0,0,0);
        ui->MainWin->show();
        //connect(Cp, SIGNAL(LoadFixtureWin_Signal()), this, SLOT(FixtureWinSlot()));
    emit ProgramButtonClicked();
}

void controller::on_pbHome_clicked()
{
    ui->textEdit->setText(ui->pbHome->text());
    emit HomeButtonClicked();
}
