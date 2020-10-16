#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QPainter>


namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker(void) {this->hide();}

private:
    void paintEvent(QPaintEvent * event) override;
    Ui::ColorPicker *ui;

};

#endif // COLORPICKER_H
