#ifndef DIALS_H
#define DIALS_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class dials;
}

class dials : public QWidget
{
    Q_OBJECT

public:
    explicit dials(QWidget *parent = nullptr);
    ~dials();

private slots:
    void on_dial_2_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_dial_3_valueChanged(int value);

    void on_dial_4_valueChanged(int value);

    void on_dial_2_sliderMoved(int position);

    void on_dial_sliderMoved(int position);

    void on_dial_3_sliderMoved(int position);

    void on_dial_4_sliderMoved(int position);

private:
    Ui::dials *ui;
    void resizeEvent(QResizeEvent *event) override;
signals:
    void DialChange_Signal(int ID, int Val);
};

#endif // DIALS_H
