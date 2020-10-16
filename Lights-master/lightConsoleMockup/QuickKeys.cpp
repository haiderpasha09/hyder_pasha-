#include "QuickKeys.h"
#include "ui_QuickKeys.h"
#include <sstream>

QuickKeys::QuickKeys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickKeys)
{
    ui->setupUi(this);
//    screen_1 screen1;
//    connect(this , SIGNAL(deleteSong_SIGNAL()) , this , SLOT(deleteSong_SLOT()));
    Change_Color(1,QColor(240,0,0));
    Change_Color(2,QColor(255, 0, 255));
    Change_Color(3,QColor(170, 0, 255));
    Change_Color(4,QColor(0, 0, 255));
    Change_Color(5,QColor(0, 170, 255));
    Change_Color(6,QColor(0, 170, 127));
    Change_Color(7,QColor(0,255, 0));
    Change_Color(8,QColor(85, 255,127));
    Change_Color(9,QColor(255, 255, 0));
    Change_Color(10,QColor(170, 85, 0));
    Change_Color(11,QColor(255, 255, 255));
}

QuickKeys::~QuickKeys()
{
    delete ui;
}

void QuickKeys::Change_Color(int iD, QColor BasColor){
    QPushButton * pbC;
    switch (iD) {
    case 1: pbC = ui->pushButton_17; break;
    case 2: pbC = ui->pushButton_25; break;
    case 3: pbC = ui->pushButton_26; break;
    case 4: pbC = ui->pushButton_27; break;
    case 5: pbC = ui->pushButton_19; break;
    case 6: pbC = ui->pushButton_24; break;
    case 7: pbC = ui->pushButton_22; break;
    case 8: pbC = ui->pushButton_20; break;
    case 9: pbC = ui->pushButton_18; break;
    case 10: pbC = ui->pushButton_23; break;
    case 11: pbC = ui->pushButton_21; break;
    default:
        pbC = 0; break;
    }
    if (pbC != 0){
    std::stringstream  g;
    QString s;
          g <<  "QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, " <<
                "stop:0 rgba("  << BasColor.red() << "," << BasColor.green() << "," << BasColor.blue() <<",255) " <<
                ", stop:1 rgba(" << BasColor.red()/3 << "," << BasColor.green()/3 << "," << BasColor.blue()/3 <<",255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 0px;border-radius: 5px;}";
          const std::string t = g.str();
          s = t.c_str();
          //qDebug() << s;
    pbC->setStyleSheet(s);
    }
}

void QuickKeys::on_pushButton_2_clicked()
{
    emit deleteSong_SIGNAL();
//    qDebug() << " Signal emitted";
}

void QuickKeys::deleteSong_SLOT()
{
  //  qDebug() << " slot called";
}

//void QuickKeys::on_pushButton_3_clicked()
//{
//    emit editSong_SIGNAL();
//}

//void QuickKeys::on_pushButton_4_clicked()
//{
//    qDebug() << this->geometry();
//}

void QuickKeys::resizeEvent(QResizeEvent *event){
    //ui->widget_2->setMinimumHeight(event->size().height()/8);
    //ui->widget->setMinimumHeight(event->size().height()*7/8);
    qDebug() << event->size();
    QWidget::resizeEvent(event);
}

void QuickKeys::on_pbDelete_clicked()
{
    emit deleteSong_SIGNAL();
}

void QuickKeys::on_pbEdit_clicked()
{
    emit editSong_SIGNAL();
}
