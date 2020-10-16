#include "colorpicker.h"
#include "ui_colorpicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)

{
    ui->setupUi(this);



//     QPainter painter;
//    painter.begin(ui->widget);
//    painter.drawArc(QRectF(10,20,80,60), 0, 40);
 //   painter.end();
}

void ColorPicker::paintEvent(QPaintEvent * event){
    QColor c;
    int Wid = ui->label->geometry().width();
    int High = ui->label->geometry().height();

    QPixmap pixmap(Wid,High);
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);
    QImage pic(Wid,High,QImage::Format_RGB32);

    for(int x=0; x < Wid; x++){
       for(int y=0; y < High; y++){
           c.setHsv(x*360/Wid,y*256/High,100);
           pic.setPixel(x,y,c.rgb());
       }
    }
    //QRect dirtyRect = ui->widget->rect();
    //painter.setRenderHint(QPainter::Antialiasing, false);
    painter.drawImage(0,0, pic);
//    painter.setBrush(QBrush(Qt::black));
//    painter.drawRect(10, 10, 100, 100);

    ui->label->setPixmap(pixmap);

    Wid = ui->label_2->geometry().width();
    High = ui->label_2->geometry().height();

    QPixmap pixmap2(Wid,High);
    pixmap2.fill(QColor("transparent"));

    QPainter painter2(&pixmap2);
    QImage pic2(Wid,High,QImage::Format_RGB32);

    for(int x=0; x < Wid; x++){
       for(int y=0; y < High; y++){
           c.setHsv(180,127,255 - y*255/High);
           pic2.setPixel(x,y,c.rgb());
       }
    }
    //QRect dirtyRect = ui->widget->rect();
    //painter.setRenderHint(QPainter::Antialiasing, false);
    painter2.drawImage(0,0, pic2);
//    painter.setBrush(QBrush(Qt::black));
//    painter.drawRect(10, 10, 100, 100);

    ui->label_2->setPixmap(pixmap2);
    QWidget::paintEvent(event);
}
