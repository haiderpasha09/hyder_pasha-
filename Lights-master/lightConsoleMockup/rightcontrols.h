#ifndef RIGHTCONTROLS_H
#define RIGHTCONTROLS_H

#include <QWidget>
#include <QDebug>
#include <QResizeEvent>

namespace Ui {
class rightControls;
}

class rightControls : public QWidget
{
    Q_OBJECT

public:
    explicit rightControls(QWidget *parent = 0);
    ~rightControls();

private slots:
    void on_pushButton_clicked();



    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_pushButton_9_clicked();



    void on_pushButton_26_clicked();

private:
    Ui::rightControls *ui;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // RIGHTCONTROLS_H
