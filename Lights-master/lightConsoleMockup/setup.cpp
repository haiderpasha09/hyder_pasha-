#include "setup.h"
#include "ui_setup.h"

Setup::Setup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setup)
{
    ui->setupUi(this);
}

Setup::~Setup()
{
    delete ui;
}

void Setup::on_btnFixtureSetup_clicked()
{
    emit LoadFixtureWin_Signal();
    ui->btnRightUp->setText("Current Fixtures");
    ui->btnRightDn->setText("Add Fixture Type");
}

void Setup::AddFixture_SLOT(QVariant vParm){
    mButtons * FixtureButton = new mButtons(this);
    ShowFixtures sfData;
    sfData = vParm.value<ShowFixtures>();
    FixtureButton->setButtonType("FixtureInShow");
    FixtureButton->setStyleSheet(blueBtnClr);
    FixtureButton->setText(sfData.Model);
    //Fixture = new mButtons(this);  // Create a dynamic button object
    ui->FixtureLayout->addWidget(FixtureButton);
    ui->Fixture_scrollArea->setMinimumHeight(ui->FixtureLayout->count()*30);
}
