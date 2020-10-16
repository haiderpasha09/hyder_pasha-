#ifndef FORM_UI101_H
#define FORM_UI101_H

#include <QWidget>

namespace Ui {
class Form_ui101;
}

class Form_ui101 : public QWidget
{
    Q_OBJECT

public:
    explicit Form_ui101(QWidget *parent = nullptr);
    ~Form_ui101();

private:
    Ui::Form_ui101 *ui;
};


#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QWidget>

class ColorSelector : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSelector(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // COLORSELECTOR_H

It
#endif // FORM_UI101_H
