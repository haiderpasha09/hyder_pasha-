#ifndef LEFTCONTROLS_H
#define LEFTCONTROLS_H

#include <QWidget>

namespace Ui {
class leftControls;
}

class leftControls : public QWidget
{
    Q_OBJECT

public:
    explicit leftControls(QWidget *parent = nullptr);
    ~leftControls();

private slots:
    //void on_verticalSlider_valueChanged(int value);

    //void on_verticalSlider_3_valueChanged(int value);

    //void on_verticalSlider_4_valueChanged(int value);

    //void on_verticalSlider_2_valueChanged(int value);

    //void on_verticalSlider_7_valueChanged(int value);

    //void on_verticalSlider_6_valueChanged(int value);

    //void on_verticalSlider_5_valueChanged(int value);

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::leftControls *ui;
};

#endif // LEFTCONTROLS_H
