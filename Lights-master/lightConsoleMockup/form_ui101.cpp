#include "form_ui101.h"
#include "ui_form_ui101.h"

Form_ui101::Form_ui101(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_ui101)
{
    ui->setupUi(this);
}

Form_ui101::~Form_ui101()
{
    delete ui;
}


ColorSelector::ColorSelector(QWidget *parent) : QWidget(parent)
{
}

void ColorSelector::paintEvent(QPaintEvent *){
    QColor c;
    QImage pic(360,20,QImage::Format_RGB32);
    for(int x=0; x < 360; x++){
       for(int y=0; y < 20; y++){
           c.setHsl(x,255,127);
           pic.setPixel(x,y,c.rgb());
           }
     }
}
