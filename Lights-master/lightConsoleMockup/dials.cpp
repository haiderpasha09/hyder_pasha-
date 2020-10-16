#include "dials.h"
#include "ui_dials.h"

dials::dials(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dials)
{
    ui->setupUi(this);
    //this->setWindowFlag(Qt::FramelessWindowHint);


}

dials::~dials()
{
    delete ui;
}

void dials::on_dial_2_valueChanged(int value)
{
//    ui->LBL->setText(QString::number(value));
}

void dials::on_dial_valueChanged(int value)
{
//    ui->LBL->setText(QString::number(value));
}

void dials::on_dial_3_valueChanged(int value)
{
//    ui->LBL->setText(QString::number(value));
}

void dials::on_dial_4_valueChanged(int value)
{
//    ui->LBL->setText(QString::number(value));
}
void dials::resizeEvent(QResizeEvent *event){
    ui->dial->setMaximumHeight(event->size().height()*3/4);
    ui->dial_2->setMaximumHeight(event->size().height()*3/4);
    ui->dial_3->setMaximumHeight(event->size().height()*3/4);
    ui->dial_4->setMaximumHeight(event->size().height()*3/4);
}

void dials::on_dial_2_sliderMoved(int position)
{
    emit DialChange_Signal(1, position);
}

void dials::on_dial_sliderMoved(int position)
{
    emit DialChange_Signal(2, position);
}

void dials::on_dial_3_sliderMoved(int position)
{
    emit DialChange_Signal(3, position);
}

void dials::on_dial_4_sliderMoved(int position)
{
    emit DialChange_Signal(4, position);
}
