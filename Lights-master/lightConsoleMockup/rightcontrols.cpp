#include "rightcontrols.h"
#include "ui_rightcontrols.h"

rightControls::rightControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rightControls)
{
    ui->setupUi(this);
}

rightControls::~rightControls()
{
    delete ui;
}

void rightControls::resizeEvent(QResizeEvent *event){
    ui->widget_2->setMinimumHeight(event->size().height()/8);
    //qDebug() << event->size();
    QSize BSize = QSize(event->size().height()/10,event->size().height()/10);
    ui->verticalSpacer_2->changeSize(10,BSize.height()*2+6);
    ui->pushButton->setMinimumSize(BSize);
    ui->pushButton_2->setMinimumSize(BSize);
    ui->pushButton_3->setMinimumSize(BSize);
    ui->pushButton_4->setMinimumSize(BSize);
    ui->pushButton_7->setMinimumSize(BSize);
    ui->pushButton_8->setMinimumSize(BSize);
    ui->pushButton_9->setMinimumSize(BSize);
    ui->pushButton_10->setMinimumSize(BSize);
    ui->pushButton_11->setMinimumSize(BSize);
    ui->pushButton_12->setMinimumSize(BSize);
    ui->pushButton_13->setMinimumSize(BSize);
    ui->pushButton_27->setMinimumSize(BSize);
    ui->pushButton_24->setMinimumSize(BSize);
    ui->pushButton_25->setMinimumSize(BSize);
    ui->pushButton_15->setMinimumSize(BSize);
    ui->pBSelect->setMinimumSize(BSize);
    ui->pushButton_19->setMinimumSize(BSize);
    ui->pushButton_12->setMinimumSize(BSize);
    ui->pushButton_29->setMinimumSize(BSize);
    ui->pushButton_30->setMinimumSize(BSize);
    ui->pushButton_31->setMinimumSize(BSize);
    QWidget::resizeEvent(event);
}

void rightControls::on_pushButton_clicked()
{
    ui->LBL->setText(ui->pushButton->text());
}

//void rightControls::on_pushButton_2_clicked()
//{
//    ui->LBL->setText(ui->pushButton_2->text());

//}

void rightControls::on_pushButton_7_clicked()
{
    ui->LBL->setText(ui->pushButton_7->text());

}

void rightControls::on_pushButton_8_clicked()
{
    ui->LBL->setText(ui->pushButton_8->text());

}

void rightControls::on_pushButton_5_clicked()
{
    ui->LBL->setText(ui->pushButton_5->text());

}

void rightControls::on_pushButton_6_clicked()
{
    ui->LBL->setText(ui->pushButton_6->text());

}

void rightControls::on_verticalSlider_valueChanged(int value)
{
    ui->LBL->setText(QString::number(value));

}

void rightControls::on_verticalSlider_2_valueChanged(int value)
{
    ui->LBL->setText(QString::number(value));

}

void rightControls::on_pushButton_9_clicked()
{

}

//void rightControls::on_pushButton_22_clicked()
//{

//}

void rightControls::on_pushButton_26_clicked()
{
    qDebug() << this->geometry();
}
