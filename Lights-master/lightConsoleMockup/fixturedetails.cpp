#include "fixturedetails.h"
#include "ui_fixturedetails.h"

FixtureDetails::FixtureDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixtureDetails)
{
    ui->setupUi(this);
}

FixtureDetails::~FixtureDetails()
{
    delete ui;
}
