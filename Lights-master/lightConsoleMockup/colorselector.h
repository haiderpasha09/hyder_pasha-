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
