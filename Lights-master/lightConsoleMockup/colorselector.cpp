#include "colorselector.h"

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
